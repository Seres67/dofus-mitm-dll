#include <WinSock2.h>

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "HookEngine.h"
#include "packets/impl/ChatMessagePacket.hpp"
#include "packets/impl/PlayerInventoryPacket.hpp"
#include "packets/PacketIds.hpp"
#include "packets/impl/MapMovementPacket.hpp"
#include "packets/impl/BasicPongPacket.hpp"
#include "packets/impl/GameContextRemoveElementPacket.hpp"
#include "packets/impl/NoMovementPacket.hpp"
#include "packets/impl/MapFightCountPacket.hpp"
#include "packets/impl/MultiTabStoragePacket.hpp"
#include "packets/impl/BasicAckPacket.hpp"
#include "packets/impl/UnknownPacket.hpp"
#include "packets/impl/BasicPingPacket.hpp"
#include "packets/factory/PacketFactory.hpp"
#include "packets/ReceivedPacketNames.hpp"
#include "packets/SentPacketNames.hpp"

const std::vector<uint16_t> unknown_ids = {

};

bool lastPacketComplete = true;
std::vector<char> recvGlobalBuffer;
std::vector<char> sendGlobalBuffer;
std::ofstream log_file;

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
//    if (length <= 5)
//        return PassthroughHook<int, sendFnc>(sendHook, socket, const_cast<char *>(buffer), length, flags);
    if (length != 65536) {
        std::unique_ptr<IPacket> packet = PacketFactory::make_packet(buffer);
//        std::cout << "sending " << length << " bytes, header: " << packet->getHeader() << ", id: " << packet->getPacketId() << std::endl;
        std::string packet_dump = packet->dump(true);
        std::cout << "sending: " << packet_dump << std::endl;
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
                std::string packet_dump = packet->dump(true);
                if (!packet_dump.empty())
                    std::cout << "sending: " << packet_dump << std::endl;
            }
            pos = t_pos;
        }
    }
    return PassthroughHook<int, sendFnc>(sendHook, socket, const_cast<char *>(buffer), length, flags);
}

int WSAAPI recvHook(SOCKET socket, char *buffer, int length, int flags) {
    if (length <= 5)
        return PassthroughHook<int, recvFnc>(recvHook, socket, buffer, length, flags);
    if (length != 65536) {
        std::unique_ptr<IPacket> packet = PacketFactory::make_packet(buffer);
        std::string packet_dump = packet->dump(false);
        if (!packet_dump.empty())
            std::cout << "receiving: " << packet_dump << std::endl;
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
                std::string packet_dump = packet->dump(false);
                if (!packet_dump.empty())
                    std::cout << "receiving: " << packet_dump << std::endl;
            }
            pos = t_pos;
        }
    }
    return PassthroughHook<int, recvFnc>(recvHook, socket, buffer, length, flags);
}

[[maybe_unused]] __declspec(dllexport) BOOL
WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, [[maybe_unused]] LPVOID reserved) {
    static HookEngine hookEngine{};

    if (dwReason == DLL_PROCESS_ATTACH) {
        log_file.open("./log.txt", std::ios_base::binary);
        ReceivedPacketNames::setup_map();
        SentPacketNames::setup_map();
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
        log_file.close();
        (void) hookEngine.Unhook(std::string_view("Ws2_32.dll"), std::string_view("send"));
        (void) hookEngine.Unhook(std::string_view("Ws2_32.dll"), std::string_view("recv"));
    }

    return TRUE;
}