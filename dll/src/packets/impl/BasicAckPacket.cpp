//
// Created by lou on 01/05/2024.
//

#include <string>
#include "packets/impl/BasicAckPacket.hpp"

BasicAckPacket::BasicAckPacket(const char *packet) : APacket(packet) {

}

std::ostream &operator<<(std::ostream &os, const BasicAckPacket &packet) {
    return os << "BasicAckPacket{}";
}

std::string BasicAckPacket::dump() const {
    return std::string("BasicAckPacket{id: " + std::to_string(m_packet_id) + "; len: " + std::to_string(getLength()) + "}");
}
