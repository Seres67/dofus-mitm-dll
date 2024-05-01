//
// Created by lou on 01/05/2024.
//

#include "BasicPongPacket.hpp"

BasicPongPacket::BasicPongPacket(const char *packet) : APacket(packet) {
    m_quiet = packet[m_pos];
}

std::ostream &operator<<(std::ostream &os, const BasicPongPacket &packet) {
    return os << "BasicPongPacket{quiet: " << packet.m_quiet << "}";
}