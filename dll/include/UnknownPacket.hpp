//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_UNKNOWNPACKET_HPP
#define DOFUS_TEST_UNKNOWNPACKET_HPP

#include <ostream>
#include "APacket.hpp"

class UnknownPacket : public APacket {
public:
    UnknownPacket(const char *packet, std::size_t len);

    friend std::ostream &operator<<(std::ostream &os, const UnknownPacket &packet);

private:
    uint16_t m_packet_id = 0;
    std::string m_data;
};

#endif //DOFUS_TEST_UNKNOWNPACKET_HPP
