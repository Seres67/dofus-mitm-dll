//
// Created by lou on 01/05/2024.
//

#include "MapMovementPacket.hpp"

MapMovementPacket::MapMovementPacket(const char *packet) : APacket(packet) {
    m_movement_size = (uint8_t) packet[m_pos] << 8 | (uint8_t) packet[m_pos + 1];
    m_pos += 2;
    for (int i = 0; i < m_movement_size; ++i) {
        m_moves.emplace_back((uint8_t) packet[m_pos] << 8 | (uint8_t) packet[m_pos + 1]);
        m_pos += 2;
    }
    m_direction = (uint8_t) packet[m_pos] << 8 | (uint8_t) packet[m_pos + 1];
    m_pos += 2;
    memcpy(&m_actor_id, &packet[m_pos], sizeof(uint64_t));
    m_pos += 8;
}

std::ostream &operator<<(std::ostream &os, const MapMovementPacket &packet) {
    os << "MapMovementPacket{size: " << packet.m_movement_size << "; moves: ";
    for (auto &&move : packet.m_moves)
        os << move << ", ";
    return os << "}";
}