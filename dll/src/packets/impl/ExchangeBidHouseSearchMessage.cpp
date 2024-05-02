//
// Created by lou on 02/05/2024.
//
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include "packets/impl/ExchangeBidHouseSearchMessage.hpp"
#include "Utils.hpp"

HANDLE retrieveProcessId(char *processName) {
    HANDLE hProcess = nullptr;
    PROCESSENTRY32 entry;
    entry.dwFlags = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (Process32First(snapshot, &entry) == 1)
        while (Process32Next(snapshot, &entry) == 1)
            if (_stricmp(entry.szExeFile, processName) == 0)
                hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, entry.th32ProcessID);
    CloseHandle(snapshot);
    return hProcess;
}

ExchangeBidHouseSearchMessage::ExchangeBidHouseSearchMessage(const char *packet) : ASentPacket(packet) {
    m_object_id = Utils::readVarUInt(packet, m_pos);
    m_follow = packet[m_pos];
    std::cout << "STARTING DEBUG" << std::endl;
    DebugActiveProcess(GetProcessId(retrieveProcessId(_strdup("Dofus.exe"))));
}

std::ostream &operator<<(std::ostream &os, const ExchangeBidHouseSearchMessage &packet) {
    return os << "ExchangeBidHouseSearchMessage{}";
}

std::string ExchangeBidHouseSearchMessage::dump() const {
    return "ExchangeBidHouseSearchMessage{obj_id: " + std::to_string(m_object_id) + ", instance_id: " + std::to_string(m_instance_id) + "}";
}
