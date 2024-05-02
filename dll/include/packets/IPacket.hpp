//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_IPACKET_HPP
#define DOFUS_TEST_IPACKET_HPP


#include <cstdint>
#include <string>

class IPacket {
public:
    virtual ~IPacket()= default;

    [[nodiscard]] virtual uint16_t getPacketId() const = 0;

    [[nodiscard]] virtual uint32_t getLength() const = 0;

    [[maybe_unused]] [[nodiscard]] virtual uint8_t getLengthType() const = 0;

    [[maybe_unused]] [[nodiscard]] virtual uint64_t getPos() const = 0;

    [[nodiscard]] virtual std::string dump() const = 0;

    [[nodiscard]] virtual uint16_t getHeader() const = 0;
};


#endif //DOFUS_TEST_IPACKET_HPP
