//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_BASICPINGPACKET_HPP
#define DOFUS_TEST_BASICPINGPACKET_HPP

#include <ostream>
#include "packets/APacket.hpp"

class BasicPingPacket : virtual public APacket {
public:
    explicit BasicPingPacket(const char *packet);

    ~BasicPingPacket() override = default;

    [[nodiscard]] std::string dump() const override;

    friend std::ostream &operator<<(std::ostream &os, const BasicPingPacket &packet);

private:
    uint16_t m_packet_id = 8285;
    bool m_quiet;
};


#endif //DOFUS_TEST_BASICPINGPACKET_HPP
