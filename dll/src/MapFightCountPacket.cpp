//
// Created by lou on 01/05/2024.
//
#include "MapFightCountPacket.hpp"

MapFightCountPacket::MapFightCountPacket(const char *packet) : APacket(packet) {

}

std::ostream &operator<<(std::ostream &os, const MapFightCountPacket &packet) {
    return os << "MapFightCountPacket{}";
}