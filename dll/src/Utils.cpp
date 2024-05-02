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
            out |= (uint8_t) buffer[pos + i] << i * 7;
            out &= ~(1 << 8);
        } else {
            out |= (uint8_t) buffer[pos + i] << i * 7;
            pos += i + 1;
            return out;
        }
    }
    pos += i;
    return out;
}

uint16_t Utils::readVarUShort(const char *buffer, std::size_t &pos) {
    uint16_t out = 0;
    int i = 0;
    for (; i < 2; ++i) {
        uint8_t byte = buffer[pos + i];
        if (byte & 0b10000000) {
            out |= (uint8_t) buffer[pos + i] << i * 7;
            out &= ~(1 << 8);
        } else {
            out |= (uint8_t) buffer[pos + i] << i * 7;
            pos += i + 1;
            return out;
        }
    }
    pos += i;
    return out;
}

uint32_t Utils::readVarUInt(const char *buffer, std::size_t &pos) {
    uint32_t out = 0;
    int i = 0;
    for (; i < 4; ++i) {
        uint8_t byte = buffer[pos + i];
        if (byte & 0b10000000) {
            out |= (uint8_t) buffer[pos + i] << i * 7;
            out &= ~(1 << 8);
        } else {
            out |= (uint8_t) buffer[pos + i] << i * 7;
            pos += i + 1;
            return out;
        }
    }
    pos += i;
    return out;
}

#include <climits>

template<typename T>
T Utils::swap_endian(T u) {
    static_assert(CHAR_BIT == 8, "CHAR_BIT != 8");

    union {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}
