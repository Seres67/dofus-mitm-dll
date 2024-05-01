//
// Created by lou on 01/05/2024.
//
#include "GameContextRemoveElementPacket.hpp"

GameContextRemoveElementPacket::GameContextRemoveElementPacket(const char *packet) : APacket(packet) {

}

std::ostream &operator<<(std::ostream &os, const GameContextRemoveElementPacket &packet) {
    return os << "GameContextRemoveElementPacket{}";
}