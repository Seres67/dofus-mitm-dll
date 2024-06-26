//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_BASICPONGPACKET_HPP
#define DOFUS_TEST_BASICPONGPACKET_HPP

#include <ostream>
#include "packets/AReceivedPacket.hpp"

class BasicPongPacket : virtual public AReceivedPacket {
public:
    explicit BasicPongPacket(const char *packet);

    ~BasicPongPacket() override = default;

    [[nodiscard]] std::string dump() const override;

    friend std::ostream &operator<<(std::ostream &os, const BasicPongPacket &packet);

private:
    uint16_t m_packet_id = 5906;
    bool m_quiet;
};


#endif //DOFUS_TEST_BASICPONGPACKET_HPP
