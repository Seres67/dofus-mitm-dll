//
// Created by lou on 01/05/2024.
//
#include <iostream>
#include "UnknownPacket.hpp"

UnknownPacket::UnknownPacket(const char *packet, std::size_t len) : APacket(packet) {
    m_data = std::string(packet, packet + len);
}

std::ostream &operator<<(std::ostream &os, const UnknownPacket &packet) {
    os.setf(std::ios::hex);
    os << "UnknownPacket{id: " << packet.m_packet_id << "; data: " << packet.m_data.c_str() << "}";
    os.unsetf(std::ios::hex);
    return os;
}