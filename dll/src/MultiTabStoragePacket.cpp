//
// Created by lou on 01/05/2024.
//
#include "MultiTabStoragePacket.hpp"

MultiTabStoragePacket::MultiTabStoragePacket(const char *packet) : APacket(packet) {

}

std::ostream &operator<<(std::ostream &os, const MultiTabStoragePacket &packet) {
    return os << "MultiTabStoragePacket{}";
}