//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_MAPMOVEMENTPACKET_HPP
#define DOFUS_TEST_MAPMOVEMENTPACKET_HPP


#include <ostream>
#include <vector>
#include "APacket.hpp"

class MapMovementPacket  : public APacket {
public:
    explicit MapMovementPacket(const char *packet);

    friend std::ostream &operator<<(std::ostream &os, const MapMovementPacket &packet);

private:
    uint16_t m_packet_id = 4955;
    uint16_t m_movement_size;
    std::vector<uint16_t> m_moves;
    uint16_t m_direction;
    uint64_t m_actor_id = 0;
};


#endif //DOFUS_TEST_MAPMOVEMENTPACKET_HPP
