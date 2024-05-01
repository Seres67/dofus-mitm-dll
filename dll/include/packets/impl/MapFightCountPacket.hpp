//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_MAPFIGHTCOUNTPACKET_HPP
#define DOFUS_TEST_MAPFIGHTCOUNTPACKET_HPP

#include <ostream>
#include "packets/APacket.hpp"

class MapFightCountPacket : virtual public APacket {
public:
    explicit MapFightCountPacket(const char *packet);

    ~MapFightCountPacket() override = default;

    std::string dump() const override;

    friend std::ostream &operator<<(std::ostream &os, const MapFightCountPacket &packet);

private:
    uint16_t m_packet_id = 213;
};

#endif //DOFUS_TEST_MAPFIGHTCOUNTPACKET_HPP
