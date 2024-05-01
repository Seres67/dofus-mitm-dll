//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_NOMOVEMENTPACKET_HPP
#define DOFUS_TEST_NOMOVEMENTPACKET_HPP

#include <ostream>
#include "packets/APacket.hpp"

class NoMovementPacket : virtual public APacket {
public:
    explicit NoMovementPacket(const char *packet);

    ~NoMovementPacket() override = default;

    std::string dump() const override;

    friend std::ostream &operator<<(std::ostream &os, const NoMovementPacket &packet);

private:
    uint16_t m_packet_id = 6782;
};

#endif //DOFUS_TEST_NOMOVEMENTPACKET_HPP
