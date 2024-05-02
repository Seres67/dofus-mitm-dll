//
// Created by lou on 02/05/2024.
//
#include "packets/impl/ContainerInventoryPacket.hpp"

ContainerInventoryPacket::ContainerInventoryPacket(const char *packet) : APacket(packet),PlayerInventoryPacket(packet) {

}

std::ostream &operator<<(std::ostream &os, [[maybe_unused]] const ContainerInventoryPacket &packet) {
    return os << "ContainerInventoryPacket{}";
}