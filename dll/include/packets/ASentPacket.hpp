//
// Created by lou on 30/04/2024.
//

#ifndef DOFUS_TEST_ASENTPACKET_HPP
#define DOFUS_TEST_ASENTPACKET_HPP

#include <cstdint>
#include <ostream>
#include "PacketIds.hpp"
#include "IPacket.hpp"

class ASentPacket : virtual public IPacket {
public:
    explicit ASentPacket(const char *packet) {
        m_header = (uint8_t) packet[m_pos] << 8 | (uint8_t) packet[m_pos + 1];
        m_packet_id = m_header >> 2;
        m_length_type = m_header & 3;
        m_pos += 2;
        m_instance_id =
                (uint8_t) packet[m_pos] << 24 | (uint8_t) packet[m_pos + 1] << 16 | (uint8_t) packet[m_pos + 2] << 8 | (uint8_t) packet[m_pos + 3];
        m_pos += 4;
        if (m_length_type == 1) {
            m_length = (uint8_t) packet[m_pos];
            ++m_pos;
        } else if (m_length_type == 2) {
            m_length = (uint8_t) packet[m_pos] << 8 | (uint8_t) packet[m_pos + 1];
            m_pos += 2;
        } else if (m_length_type == 3) {
            m_length = (uint8_t) packet[m_pos] << 16 | (uint8_t) packet[m_pos + 1] << 8 | (uint8_t) packet[m_pos + 2];
            m_pos += 3;
        }
    }

    ~ASentPacket() override = default;

    [[nodiscard]] uint16_t getPacketId() const override {
        return m_packet_id;
    }

    [[nodiscard]] uint32_t getLength() const override {
        return m_length;
    }

    [[nodiscard]] uint8_t getLengthType() const override {
        return m_length_type;
    }

    [[nodiscard]] uint64_t getPos() const override {
        return m_pos;
    }

    [[nodiscard]] std::string dump() const override {
        return "ASentPacket{}";
    }

    [[nodiscard]] uint16_t getHeader() const override {
        return m_header;
    }

    uint32_t getMaxLength() const override {
        return UINT32_MAX;
    }
protected:
    uint16_t m_header = 0;
    uint16_t m_packet_id = 0;
    uint8_t m_length_type = 0;
    uint32_t m_instance_id = 0;
    uint32_t m_length = 0;
    uint64_t m_pos = 0;
};


#endif //DOFUS_TEST_ASENTPACKET_HPP
