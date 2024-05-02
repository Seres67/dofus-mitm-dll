//
// Created by lou on 01/05/2024.
//
#include <string>
#include "packets/impl/MapFightCountPacket.hpp"

MapFightCountPacket::MapFightCountPacket(const char *packet) : APacket(packet) {

}

std::ostream &operator<<(std::ostream &os, [[maybe_unused]] const MapFightCountPacket &packet) {
    return os << "MapFightCountPacket{}";
}

std::string MapFightCountPacket::dump() const {
    return std::string("MapFightCountPacket{id: " + std::to_string(m_packet_id) + "; len: " + std::to_string(getLength()) + "}");
}
