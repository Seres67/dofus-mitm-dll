//
// Created by lou on 01/05/2024.
//
#include <string>
#include "packets/impl/NoMovementPacket.hpp"

NoMovementPacket::NoMovementPacket(const char *packet) : APacket(packet) {

}

std::ostream &operator<<(std::ostream &os, const NoMovementPacket &packet) {
    return os << "NoMovementPacket{}";
}

std::string NoMovementPacket::dump() const {
    return std::string("NoMovementPacket{id: " + std::to_string(m_packet_id) + "; len: " + std::to_string(getLength()) + "}");
}
