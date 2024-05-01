//
// Created by lou on 01/05/2024.
//

#include "BasicAckPacket.hpp"

BasicAckPacket::BasicAckPacket(const char *packet) : APacket(packet) {

}

std::ostream &operator<<(std::ostream &os, const BasicAckPacket &packet) {
    return os << "BasicAckPacket{}";
}