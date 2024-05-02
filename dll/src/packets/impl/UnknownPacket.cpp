//
// Created by lou on 01/05/2024.
//
#include <iostream>
#include <string>
#include "packets/impl/UnknownPacket.hpp"
#include "packets/ReceivedPacketNames.hpp"
#include "packets/SentPacketNames.hpp"

UnknownPacket::UnknownPacket(const char *packet) : APacket(packet) {
//    m_data = std::string(packet, packet + len);
}

std::ostream &operator<<(std::ostream &os, const UnknownPacket &packet) {
    return os << "UnknownPacket{id: " << packet.m_packet_id << "; len: " << packet.getLength() << "}";
}

std::string UnknownPacket::dump() const {
    std::string r_packet_name = ReceivedPacketNames::get_packet_name(m_packet_id);
    std::string s_packet_name = SentPacketNames::get_packet_name(m_packet_id);
    if (!r_packet_name.empty())
        return std::string(r_packet_name + "{id: " + std::to_string(m_packet_id) + "; len: " +
                           std::to_string(getLength()) + "}");
    else if (!s_packet_name.empty())
        return std::string(s_packet_name + "{id: " + std::to_string(m_packet_id) + "; len: " +
                           std::to_string(getLength()) + "}");
    else
        return "";
}
