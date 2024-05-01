//
// Created by lou on 01/05/2024.
//

#include <string>
#include <iostream>
#include "packets/impl/PlayerInventoryPacket.hpp"

PlayerInventoryPacket::PlayerInventoryPacket(const char *packet) : APacket(packet) {
    std::cout <<"header: " << m_header << std::endl;
    m_inventory_size = (uint8_t) packet[m_pos] << 8 | (uint8_t) packet[m_pos + 1];
    m_pos += 2;
    for (int i =0; i < m_inventory_size; ++i) {
        m_inventory_content.emplace_back(packet, m_pos);
    }
}

std::ostream &operator<<(std::ostream &os, const PlayerInventoryPacket &packet) {
    return os << "PlayerInventoryPacket{size: " << packet.m_inventory_size << "}";
}

std::string PlayerInventoryPacket::dump() const {
    return std::string(
            "PlayerInventoryPacket{id: " + std::to_string(m_packet_id) + "; len: " + std::to_string(getLength()) + "; inv_size: " +
            std::to_string(m_inventory_size) +
            "}");
}
