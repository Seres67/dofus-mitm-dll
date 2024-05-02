//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_BASICACKPACKET_HPP
#define DOFUS_TEST_BASICACKPACKET_HPP


#include <ostream>
#include "packets/AReceivedPacket.hpp"

class BasicAckPacket : virtual public AReceivedPacket {
public:
    explicit BasicAckPacket(const char *packet);

    ~BasicAckPacket() override = default;

    [[nodiscard]] std::string dump() const override;

    friend std::ostream &operator<<(std::ostream &os, const BasicAckPacket &packet);

private:
    uint16_t m_packet_id = 4642;
};


#endif //DOFUS_TEST_BASICACKPACKET_HPP
