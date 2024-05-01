//
// Created by lou on 30/04/2024.
//

#ifndef DOFUS_TEST_APACKET_HPP
#define DOFUS_TEST_APACKET_HPP

#include <cstdint>

class APacket {
public:
    explicit APacket(const char *packet) {
        m_packet_id = (uint8_t) packet[m_pos] << 6 | (uint8_t) (packet[m_pos + 1] & 0b11111100) >> 2;
        m_length_type = packet[m_pos + 1] & 0b00000011;
        m_pos += 2;
        if (m_length_type == 1) {
            m_length = (uint8_t) packet[m_pos];
            ++m_pos;
        }
        else if (m_length_type == 2) {
            m_length = (uint8_t) packet[m_pos] << 8 | (uint8_t) packet[m_pos + 1];
            m_pos += 2;
        }
        else if (m_length_type == 3) {
            m_length = (uint8_t) packet[m_pos] << 16 | (uint8_t) packet[m_pos + 1] << 8 | (uint8_t) packet[m_pos + 2];
            m_pos += 3;
        }
    }
protected:
    uint16_t m_packet_id;
    uint8_t m_length_type;
    uint32_t m_length;
    uint64_t m_pos = 0;
};


#endif //DOFUS_TEST_APACKET_HPP
