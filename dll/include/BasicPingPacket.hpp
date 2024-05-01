//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_BASICPINGPACKET_HPP
#define DOFUS_TEST_BASICPINGPACKET_HPP

#include <ostream>
#include "APacket.hpp"

class BasicPingPacket : public APacket {
public:
    explicit BasicPingPacket(const char *packet);

    friend std::ostream &operator<<(std::ostream &os, const BasicPingPacket &packet);

private:
    uint16_t m_packet_id = 8285;
    bool m_quiet;
};


#endif //DOFUS_TEST_BASICPINGPACKET_HPP
