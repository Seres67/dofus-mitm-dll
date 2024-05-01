//
// Created by lou on 02/05/2024.
//

#ifndef DOFUS_TEST_CONTAINERINVENTORYPACKET_HPP
#define DOFUS_TEST_CONTAINERINVENTORYPACKET_HPP

#include <ostream>
#include "packets/impl/PlayerInventoryPacket.hpp"

class ContainerInventoryPacket : public PlayerInventoryPacket {
public:
    explicit ContainerInventoryPacket(const char *packet);

    friend std::ostream &operator<<(std::ostream &os, const ContainerInventoryPacket &packet);

private:
    uint16_t m_packet_id = 1606;
};

#endif //DOFUS_TEST_CONTAINERINVENTORYPACKET_HPP
