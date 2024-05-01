//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_BASICACKPACKET_HPP
#define DOFUS_TEST_BASICACKPACKET_HPP


#include <ostream>
#include "APacket.hpp"

class BasicAckPacket : public APacket {
public:
    explicit BasicAckPacket(const char *packet);

    friend std::ostream &operator<<(std::ostream &os, const BasicAckPacket &packet);

private:
    uint16_t m_packet_id = 4642;
};


#endif //DOFUS_TEST_BASICACKPACKET_HPP
