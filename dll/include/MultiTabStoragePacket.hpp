//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_MULTITABSTORAGEPACKET_HPP
#define DOFUS_TEST_MULTITABSTORAGEPACKET_HPP

#include <ostream>
#include "APacket.hpp"

class MultiTabStoragePacket : public APacket {
public:
    explicit MultiTabStoragePacket(const char *packet);

    friend std::ostream &operator<<(std::ostream &os, const MultiTabStoragePacket &packet);

private:
    uint16_t m_packet_id = 3530;
};

#endif //DOFUS_TEST_MULTITABSTORAGEPACKET_HPP
