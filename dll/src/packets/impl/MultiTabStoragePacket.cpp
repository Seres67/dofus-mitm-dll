//
// Created by lou on 01/05/2024.
//
#include <string>
#include "packets/impl/MultiTabStoragePacket.hpp"

MultiTabStoragePacket::MultiTabStoragePacket(const char *packet) : AReceivedPacket(packet) {

}

std::ostream &operator<<(std::ostream &os, [[maybe_unused]] const MultiTabStoragePacket &packet) {
    return os << "MultiTabStoragePacket{}";
}

std::string MultiTabStoragePacket::dump() const {
    return std::string("MultiTabStoragePacket{id: " + std::to_string(m_packet_id) + "; len: " + std::to_string(getLength()) + "}");
}
