//
// Created by lou on 01/05/2024.
//
#include <string>
#include "packets/impl/BasicPingPacket.hpp"

BasicPingPacket::BasicPingPacket(const char *packet) : AReceivedPacket(packet) {
    m_quiet = packet[m_pos];
}

std::ostream &operator<<(std::ostream &os, const BasicPingPacket &packet) {
    return os << "BasicPingPacket{quiet: " << packet.m_quiet << "}";
}

std::string BasicPingPacket::dump() const {
    return std::string(
            "BasicPingPacket{id: " + std::to_string(m_packet_id) + "; len: " + std::to_string(getLength()) + "; quiet: " + std::to_string(m_quiet) +
            "}");
}
