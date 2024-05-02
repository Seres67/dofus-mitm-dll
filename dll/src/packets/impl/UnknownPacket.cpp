//
// Created by lou on 01/05/2024.
//
#include <iostream>
#include <string>
#include "packets/impl/UnknownPacket.hpp"
#include "packets/PacketNames.hpp"

UnknownPacket::UnknownPacket(const char *packet) : AReceivedPacket(packet) {
//    m_data = std::string(packet, packet + len);
}

std::ostream &operator<<(std::ostream &os, const UnknownPacket &packet) {
    return os << "UnknownPacket{id: " << packet.m_packet_id << "; len: " << packet.getLength() << "}";
}

std::string UnknownPacket::dump() const {
    std::string packet_name = PacketNames::get_packet_name(m_packet_id);
    if (!packet_name.empty())
        return std::string(packet_name + "{header: " + std::to_string(m_header) + "; id: " + std::to_string(m_packet_id) + "; len: " +
                           std::to_string(getLength()) + "}");
    else
        return "";
}
