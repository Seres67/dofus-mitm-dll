#include <iostream>
#include <string>

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "../include/HookEngine.h"
#include "../include/ChatMessagePacket.hpp"
#include "PlayerInventoryPacket.hpp"
#include "PacketIds.hpp"
#include "MapMovementPacket.hpp"
#include "BasicPongPacket.hpp"
#include "GameContextRemoveElementPacket.hpp"
#include "NoMovementPacket.hpp"
#include "MapFightCountPacket.hpp"
#include "MultiTabStoragePacket.hpp"
#include "BasicAckPacket.hpp"
#include "UnknownPacket.hpp"

const std::vector<uint16_t> unknown_ids = {

};

bool lastPacketComplete = true;
std::vector<char> recvGlobalBuffer;
std::vector<char> sendGlobalBuffer;

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
//    sendGlobalBuffer.insert(sendGlobalBuffer.end(), buffer, buffer + length);
    if (length != 65535) {
        uint16_t packet_id = (uint8_t) buffer[0] << 8 | (uint8_t) buffer[1];
        packet_id >>= 2;
        std::cout << "send " << packet_id << ": ";
        if (packet_id == std::to_underlying(PacketIds::ChatMessage)) {
            ChatMessagePacket packet(buffer);
            std::cout << packet << std::endl;
        } else if (packet_id == std::to_underlying(PacketIds::MapMovement)) {
            MapMovementPacket packet(buffer);
            std::cout << packet << std::endl;
        } else if (packet_id == std::to_underlying(PacketIds::GameContextRemoveElement)) {
            GameContextRemoveElementPacket packet(buffer);
            std::cout << packet << std::endl;
        } else if (packet_id == std::to_underlying(PacketIds::MapNoMovement)) {
            NoMovementPacket packet(buffer);
            std::cout << packet << std::endl;
        } else if (packet_id == std::to_underlying(PacketIds::MapFightCount)) {
            MapFightCountPacket packet(buffer);
            std::cout << packet << std::endl;
        } else if (packet_id == std::to_underlying(PacketIds::MultiTabStorage)) {
            MultiTabStoragePacket packet(buffer);
            std::cout << packet << std::endl;
        } else if (packet_id == std::to_underlying(PacketIds::BasicAck)) {
            BasicAckPacket packet(buffer);
            std::cout << packet << std::endl;
        } else if (packet_id == std::to_underlying(PacketIds::PlayerInventory)) {
            PlayerInventoryPacket packet(buffer);
            std::cout << packet << std::endl;
        } else if (packet_id == std::to_underlying(PacketIds::Pong)) {
            BasicPongPacket packet(buffer);
            std::cout << packet << std::endl;
        } else if (std::find(unknown_ids.begin(), unknown_ids.end(), packet_id) != unknown_ids.end()) {
            std::cout << std::endl;
        } else {
            std::cout << "unimplemented packet id" << std::endl;
        }
    }
    return PassthroughHook<int, sendFnc>(sendHook, socket, const_cast<char *>(buffer), length, flags);
}

int WSAAPI recvHook(SOCKET socket, char *buffer, int length, int flags) {
    if (length != 65535) {
        if (!lastPacketComplete) {
            recvGlobalBuffer.insert(recvGlobalBuffer.end(), buffer, buffer + length);
            std::string raw_packet(recvGlobalBuffer.begin(), recvGlobalBuffer.end());
            uint16_t packet_id = (uint8_t) raw_packet[0] << 8 | (uint8_t) raw_packet[1];
            packet_id >>= 2;
            std::cout << "recv " << packet_id << ": ";
            if (packet_id == std::to_underlying(PacketIds::ChatMessage)) {
                ChatMessagePacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (packet_id == std::to_underlying(PacketIds::MapMovement)) {
                MapMovementPacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (packet_id == std::to_underlying(PacketIds::GameContextRemoveElement)) {
                GameContextRemoveElementPacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (packet_id == std::to_underlying(PacketIds::MapNoMovement)) {
                NoMovementPacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (packet_id == std::to_underlying(PacketIds::MapFightCount)) {
                MapFightCountPacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (packet_id == std::to_underlying(PacketIds::MultiTabStorage)) {
                MultiTabStoragePacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (packet_id == std::to_underlying(PacketIds::BasicAck)) {
                BasicAckPacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (packet_id == std::to_underlying(PacketIds::PlayerInventory)) {
                PlayerInventoryPacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (packet_id == std::to_underlying(PacketIds::Pong)) {
                BasicPongPacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (std::find(unknown_ids.begin(), unknown_ids.end(), packet_id) != unknown_ids.end()) {
                UnknownPacket packet(raw_packet.c_str(), raw_packet.length());
                std::cout << packet << std::endl;
            } else {
                std::cout << "unimplemented packet id" << std::endl;
            }
            recvGlobalBuffer.clear();
            lastPacketComplete = true;
        } else {
            std::string raw_packet(buffer);
            uint16_t packet_id = (uint8_t) raw_packet[0] << 8 | (uint8_t) raw_packet[1];
            packet_id >>= 2;
            std::cout << "recv " << packet_id << ": ";
            if (packet_id == std::to_underlying(PacketIds::ChatMessage)) {
                ChatMessagePacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (packet_id == std::to_underlying(PacketIds::MapMovement)) {
                MapMovementPacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (packet_id == std::to_underlying(PacketIds::GameContextRemoveElement)) {
                GameContextRemoveElementPacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (packet_id == std::to_underlying(PacketIds::MapNoMovement)) {
                NoMovementPacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (packet_id == std::to_underlying(PacketIds::MapFightCount)) {
                MapFightCountPacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (packet_id == std::to_underlying(PacketIds::MultiTabStorage)) {
                MultiTabStoragePacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (packet_id == std::to_underlying(PacketIds::BasicAck)) {
                BasicAckPacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (packet_id == std::to_underlying(PacketIds::PlayerInventory)) {
                PlayerInventoryPacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (packet_id == std::to_underlying(PacketIds::Pong)) {
                BasicPongPacket packet(raw_packet.c_str());
                std::cout << packet << std::endl;
            } else if (std::find(unknown_ids.begin(), unknown_ids.end(), packet_id) != unknown_ids.end()) {
                UnknownPacket packet(raw_packet.c_str(), raw_packet.length());
                std::cout << packet << std::endl;
            } else {
                std::cout << "unimplemented packet id" << std::endl;
            }
            recvGlobalBuffer.clear();
            lastPacketComplete = true;
        }
    } else {
        recvGlobalBuffer.insert(recvGlobalBuffer.end(), buffer, buffer + length);
        lastPacketComplete = false;
    }
    return PassthroughHook<int, recvFnc>(recvHook, socket, buffer, length, flags);
}

[[maybe_unused]] __declspec(dllexport) BOOL
WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, [[maybe_unused]] LPVOID reserved) {
    static HookEngine hookEngine{};

    if (dwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        if (AllocConsole()) {
            freopen_s((FILE **) stdout, "CONOUT$", "w", stdout);
            freopen_s((FILE **) stdout, "CONOUT$", "w", stderr);
            SetConsoleTitle(reinterpret_cast<LPCSTR>(L"Console"));
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::cerr << "DLL Loaded" << std::endl;
        }

        (void) hookEngine.Hook("ws2_32.dll", "send", sendHook);
        (void) hookEngine.Hook("ws2_32.dll", "recv", recvHook);
    }

    if (dwReason == DLL_PROCESS_DETACH) {
        (void) hookEngine.Unhook(std::string_view("Ws2_32.dll"), std::string_view("send"));
        (void) hookEngine.Unhook(std::string_view("ws2_32.dll"), std::string_view("recv"));
    }

    return TRUE;
}