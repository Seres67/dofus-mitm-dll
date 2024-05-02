//
// Created by lou on 01/05/2024.
//

#include <string>
#include "packets/impl/BasicPongPacket.hpp"

BasicPongPacket::BasicPongPacket(const char *packet) : AReceivedPacket(packet) {
    m_quiet = packet[m_pos];
}

std::ostream &operator<<(std::ostream &os, const BasicPongPacket &packet) {
    return os << "BasicPongPacket{quiet: " << packet.m_quiet << "}";
}

std::string BasicPongPacket::dump() const {
    return std::string(
            "BasicPongPacket{id: " + std::to_string(m_packet_id) + "; len: " + std::to_string(getLength()) + "; quiet: " + std::to_string(m_quiet) +
            "}");
}
