//
// Created by lou on 02/05/2024.
//

#include <iostream>
#include "Utils.hpp"

uint64_t Utils::readVarULong(const char *buffer, std::size_t &pos) {
    uint64_t out = 0;
    int i = 0;
    for (; i < 8; ++i) {
        uint8_t byte = buffer[pos + i];
        if (byte & 0b10000000) {
            out |= (uint8_t) buffer[pos + i];
            out &= ~(1 << 8);
        } else {
            out |= (uint8_t) buffer[pos + i];
            out <<= (8 - i) * 8;
            pos += i + 1;
            return out;
        }
        out <<= 8;
    }
    pos += i;
    return out;
}

uint16_t Utils::readVarUShort(const char *buffer, std::size_t &pos) {
    uint16_t out;
    uint8_t byte = buffer[pos];
    if (byte & 0b10000000) {
        out = (uint8_t) buffer[pos] << 8 | (uint8_t) buffer[pos + 1];
        out &= ~(1 << 16);
        pos += 2;
    } else {
        out = (uint8_t) buffer[pos] << 8;
        ++pos;
    }
    return out;
}

uint32_t Utils::readVarUInt(const char *buffer, std::size_t &pos) {
    uint32_t out = 0;
    int i = 0;
    for (; i < 4; ++i) {
        uint8_t byte = buffer[pos + i];
        std::cout << +byte << " & " << +(byte & 0b10000000) << std::endl;
        if (byte & 0b10000000) {
            out |= (uint8_t) buffer[pos + i];
            out &= ~(1 << 8);
            out <<= 8;
        } else {
            out |= (uint8_t) buffer[pos + i];
            out <<= (4 - i) * 8;
            pos += i + 1;
            return out;
        }
    }
    pos += i;
    return out;
}
