//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_GAMECONTEXTREMOVEELEMENTPACKET_HPP
#define DOFUS_TEST_GAMECONTEXTREMOVEELEMENTPACKET_HPP

#include <ostream>
#include "APacket.hpp"

class GameContextRemoveElementPacket : public APacket {
public:
    explicit GameContextRemoveElementPacket(const char *packet);

    friend std::ostream &operator<<(std::ostream &os, const GameContextRemoveElementPacket &packet);

private:
    uint16_t m_packet_id = 1463;
};

#endif //DOFUS_TEST_GAMECONTEXTREMOVEELEMENTPACKET_HPP
