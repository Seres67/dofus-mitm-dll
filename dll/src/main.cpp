#include <WinSock2.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <mutex>
#include <deque>
#include "HookEngine.h"
#include "packets/impl/ChatMessagePacket.hpp"
#include "packets/impl/UnknownPacket.hpp"
#include "packets/factory/PacketFactory.hpp"
#include "packets/PacketNames.hpp"

//std::ofstream log_file;

using sendFnc = int (WSAAPI *)(SOCKET, const char *, int, int);
using recvFnc = int (WSAAPI *)(SOCKET, char *, int, int);

template<typename ReturnType, typename FunctionType>
ReturnType PassthroughHook(void *caller, SOCKET socket, char *buffer, int length, int flags) {
    auto original{(FunctionType) HookEngine::GetOriginalAddressFromHook(caller)};
    ReturnType result{};
    if (original != nullptr) {
        result = original(socket, buffer, length, flags);
    }

    return result;
}

int WSAAPI sendHook(SOCKET socket, const char *buffer, int length, int flags) {
    if (length != 65536) {
        std::unique_ptr<IPacket> packet = PacketFactory::make_packet(buffer);
        std::string packet_dump = packet->dump();
        if (!packet_dump.empty()) {
            std::cout << "sending: " << packet_dump << std::endl;
//            log_file << "sending: " << packet_dump << std::endl;
        }
    } else {
        uint32_t pos = 0;
        uint32_t t_pos;
        while (pos < length) {
            t_pos = pos;
            UnknownPacket _packet(&buffer[t_pos]);
            bool looks_valid = false;
            t_pos += 3;
            if (_packet.getPacketId() < 10 || _packet.getPacketId() >= 10000 || _packet.getLengthType() == 0 || _packet.getLength() == 0) {
                pos = t_pos;
                continue;
            }
            if (_packet.getLengthType() == 1 && _packet.getLength() < 256) {
                t_pos += _packet.getLength();
                looks_valid = true;
            }
            if (_packet.getLengthType() == 2 && _packet.getLength() > 256 && _packet.getLength() < 65536) {
                t_pos += _packet.getLength();
                looks_valid = true;
            }
            if (_packet.getLengthType() == 3 && _packet.getLength() > 65536 && _packet.getLength() < 16777216) {
                t_pos += _packet.getLength();
                looks_valid = true;
            }
            if (looks_valid) {
                std::unique_ptr<IPacket> packet = PacketFactory::make_packet(&buffer[pos]);
                std::string packet_dump = packet->dump();
                if (!packet_dump.empty()) {
//                    log_file << "sending: " << packet_dump << std::endl;
                    std::cout << "sending: " << packet_dump << std::endl;
                }
            }
            pos = t_pos;
        }
    }
    return PassthroughHook<int, sendFnc>(sendHook, socket, const_cast<char *>(buffer), length, flags);
}

std::vector<char> recvBuffer;
std::mutex bufferMutex;
bool running = true;

void processDataAsync() {
    while (running) {
        while (recvBuffer.size() >= 5) {
            // get packet header
            std::vector<char> tmp;
            {
                std::lock_guard<std::mutex> lock(bufferMutex);
                tmp = std::vector(recvBuffer.begin(), recvBuffer.begin() + 5);
            }
            uint64_t m_pos = 0;
            uint16_t m_header = (uint8_t) tmp[m_pos] << 8 | (uint8_t) tmp[m_pos + 1];
            uint16_t m_packet_id = m_header >> 2;
            uint8_t m_length_type = m_header & 3;
            m_pos += 2;
            // check if packet id is valid
            if (PacketNames::get_packet_name(m_packet_id).empty()) {
                {
                    std::lock_guard<std::mutex> lock(bufferMutex);
                    recvBuffer.erase(recvBuffer.begin());
                }
                break;
            }
            // check if length type is correct
            if (m_length_type == 0 || m_length_type > 3) {
                {
                    std::lock_guard<std::mutex> lock(bufferMutex);
                    recvBuffer.erase(recvBuffer.begin());
                    std::cout << "invalid length type" << std::endl;
                }
                break;
            }
            // get packet data length
            uint32_t m_length = 0;
            if (m_length_type == 1) {
                m_length = (uint8_t) tmp[m_pos];
            } else if (m_length_type == 2)
                m_length = (uint8_t) tmp[m_pos] << 8 | (uint8_t) tmp[m_pos + 1];
            else if (m_length_type == 3)
                m_length = (uint8_t) tmp[m_pos] << 16 | (uint8_t) tmp[m_pos + 1] << 8 | (uint8_t) tmp[m_pos + 2];
            // check if length is valid
            if (m_length == 0) {
                {
                    std::lock_guard<std::mutex> lock(bufferMutex);
                    recvBuffer.erase(recvBuffer.begin());
                    std::cout << "invalid length" << std::endl;
                }
                break;
            }
            if ((m_length_type == 1 && m_length < 256) || (m_length_type == 2 && m_length >= 256 && m_length < 65536) ||
                (m_length_type == 3 && m_length >= 65536 && m_length < 16777216)) {
            } else {
                {
                    std::lock_guard<std::mutex> lock(bufferMutex);
                    recvBuffer.erase(recvBuffer.begin());
                }
                break;
            }
            //check if buffer has enough data
            if (recvBuffer.size() < m_length + 3)
                break;
            std::cout << "valid " << m_header << " " << m_packet_id << " " << +m_length_type << " len:" << m_length
                      << std::endl;
            //get packet data
            std::unique_ptr<char[]> buffer(new char[m_length + 3]);
            {
                std::lock_guard<std::mutex> lock(bufferMutex);
                memcpy_s(buffer.get(), m_length + 3, recvBuffer.data(), m_length + 3);
                recvBuffer.erase(recvBuffer.begin(), recvBuffer.begin() + m_length + 2);
            }
            //parse packet data
            std::unique_ptr<IPacket> packet = PacketFactory::make_packet(buffer.get());
            std::cout << "received " << packet->dump() << std::endl;
        }
    }
}


int WSAAPI recvHook(SOCKET socket, char *buffer, int length, int flags) {
//    if (length < 5)
//        return PassthroughHook<int, recvFnc>(recvHook, socket, buffer, length, flags);
//    if (length != 65536) {
//        std::unique_ptr<IPacket> packet = PacketFactory::make_packet(buffer);
//        std::string packet_dump = packet->dump();
//        if (!packet_dump.empty()) {
//            std::cout << "receiving: " << packet_dump << std::endl;
//            log_file << "receiving: " << packet_dump << std::endl;
//        }
//    } else {
//        uint32_t pos = 0;
//        uint32_t t_pos;
//        while (pos < length) {
//            t_pos = pos;
//            UnknownPacket _packet(&buffer[t_pos]);
//            bool looks_valid = false;
//            t_pos += 3;
//            if (_packet.getPacketId() < 10 || _packet.getPacketId() >= 10000 || _packet.getLengthType() == 0 || _packet.getLength() == 0) {
//                pos = t_pos;
//                continue;
//            }
//            if (_packet.getLengthType() == 1 && _packet.getLength() < 256) {
//                t_pos += _packet.getLength();
//                looks_valid = true;
//            }
//            if (_packet.getLengthType() == 2 && _packet.getLength() >= 256 && _packet.getLength() < 65536) {
//                t_pos += _packet.getLength();
//                looks_valid = true;
//            }
//            if (_packet.getLengthType() == 3 && _packet.getLength() >= 65536 && _packet.getLength() < 16777216) {
//                t_pos += _packet.getLength();
//                looks_valid = true;
//            }
//            if (looks_valid) {
//                std::unique_ptr<IPacket> packet = PacketFactory::make_packet(&buffer[pos]);
//                std::string packet_dump = packet->dump();
//                if (!packet_dump.empty()) {
//                    std::cout << "receiving: " << packet_dump << std::endl;
//                    log_file << "receiving: " << packet_dump << std::endl;
//                }
//            }
//            pos = t_pos;
//        }
//    }
    uint16_t m_header = (uint8_t) buffer[0] << 8 | (uint8_t) buffer[1];
    uint16_t m_packet_id = m_header >> 2;
    std::cout << "main thread: " << m_header << " " << m_packet_id << " " + PacketNames::get_packet_name(m_packet_id) << std::endl;
    {
        std::lock_guard<std::mutex> lock(bufferMutex);
        recvBuffer.insert(recvBuffer.end(), buffer, buffer + length);
    }
    return PassthroughHook<int, recvFnc>(recvHook, socket, buffer, length, flags);
}

[[maybe_unused]] __declspec(dllexport) BOOL
WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, [[maybe_unused]] LPVOID reserved) {
    static HookEngine hookEngine{};
    std::thread dataProcessingThread(processDataAsync);

    if (dwReason == DLL_PROCESS_ATTACH) {
//        log_file.open("./log.txt", std::ios_base::binary);
        PacketNames::setup_map();
        DisableThreadLibraryCalls(hModule);
        if (AllocConsole()) {
            freopen_s((FILE **) stdout, "CONOUT$", "w", stdout);
            freopen_s((FILE **) stdout, "CONOUT$", "w", stderr);
            SetConsoleTitle(reinterpret_cast<LPCSTR>(L"Console"));
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::cerr << "DLL Loaded" << std::endl;
        }

        (void) hookEngine.Hook("Ws2_32.dll", "send", sendHook);
        (void) hookEngine.Hook("Ws2_32.dll", "recv", recvHook);
    }

    if (dwReason == DLL_PROCESS_DETACH) {
//        log_file.close();
        running = false;
        dataProcessingThread.join();
        (void) hookEngine.Unhook(std::string_view("Ws2_32.dll"), std::string_view("send"));
        (void) hookEngine.Unhook(std::string_view("Ws2_32.dll"), std::string_view("recv"));
    }

    return TRUE;
}