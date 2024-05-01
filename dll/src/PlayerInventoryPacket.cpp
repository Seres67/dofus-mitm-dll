//
// Created by lou on 01/05/2024.
//

#include "PlayerInventoryPacket.hpp"

PlayerInventoryPacket::PlayerInventoryPacket(const char *packet) : APacket(packet) {
    m_inventory_size = (uint8_t) packet[m_pos] << 8 | (uint8_t) packet[m_pos + 1];
    m_pos += 2;
}

std::ostream &operator<<(std::ostream &os, const PlayerInventoryPacket &packet) {
    return os << "PlayerInventoryPacket{size: " << packet.m_inventory_size << "}";
}