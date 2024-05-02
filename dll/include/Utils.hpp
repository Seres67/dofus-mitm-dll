//
// Created by lou on 02/05/2024.
//

#ifndef DOFUS_TEST_UTILS_HPP
#define DOFUS_TEST_UTILS_HPP


#include <cstdint>
#include <cstddef>

class Utils {
public:
    static uint64_t readVarULong(const char *buffer, std::size_t &pos);
    static uint32_t readVarUInt(const char *buffer, std::size_t &pos);
    static uint16_t readVarUShort(const char *buffer, std::size_t &pos);

    template<typename T>
    static T swap_endian(T u);
};


#endif //DOFUS_TEST_UTILS_HPP
