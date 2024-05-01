//
// Created by lou on 01/05/2024.
//
#include "BasicPingPacket.hpp"

BasicPingPacket::BasicPingPacket(const char *packet) : APacket(packet) {
    m_quiet = packet[m_pos];
}

std::ostream &operator<<(std::ostream &os, const BasicPingPacket &packet) {
    return os << "BasicPingPacket{quiet: " << packet.m_quiet << "}";
}