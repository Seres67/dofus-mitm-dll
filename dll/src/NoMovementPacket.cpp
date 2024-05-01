//
// Created by lou on 01/05/2024.
//
#include "NoMovementPacket.hpp"

NoMovementPacket::NoMovementPacket(const char *packet) : APacket(packet) {

}

std::ostream &operator<<(std::ostream &os, const NoMovementPacket &packet) {
    return os << "NoMovementPacket{}";
}