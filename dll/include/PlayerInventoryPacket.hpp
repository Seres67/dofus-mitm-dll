//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_PLAYERINVENTORYPACKET_HPP
#define DOFUS_TEST_PLAYERINVENTORYPACKET_HPP

#include <ostream>
#include <cstdint>
#include "APacket.hpp"

class PlayerInventoryPacket : public APacket {
public:
    explicit PlayerInventoryPacket(const char *packet);

    friend std::ostream &operator<<(std::ostream &os, const PlayerInventoryPacket &packet);

private:
    uint16_t m_packet_id = 8307;
    uint16_t m_inventory_size;
};


#endif //DOFUS_TEST_PLAYERINVENTORYPACKET_HPP
