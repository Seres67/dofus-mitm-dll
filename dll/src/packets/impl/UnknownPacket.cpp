//
// Created by lou on 01/05/2024.
//
#include <iostream>
#include <string>
#include "packets/impl/UnknownPacket.hpp"

UnknownPacket::UnknownPacket(const char *packet) : APacket(packet) {
//    m_data = std::string(packet, packet + len);
}

std::ostream &operator<<(std::ostream &os, const UnknownPacket &packet) {
    return os << "UnknownPacket{id: " << packet.m_packet_id << "; len: " << packet.getLength() << "}";
}

std::string UnknownPacket::dump() const {
    return std::string("UnknownPacket{id: " + std::to_string(m_packet_id) + "; len: " + std::to_string(getLength()) + "}");
}
