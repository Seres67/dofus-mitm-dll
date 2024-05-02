//
// Created by lou on 02/05/2024.
//

#ifndef DOFUS_TEST_EXCHANGEBIDHOUSESEARCHMESSAGE_HPP
#define DOFUS_TEST_EXCHANGEBIDHOUSESEARCHMESSAGE_HPP

#include <ostream>
#include "packets/ASentPacket.hpp"

class ExchangeBidHouseSearchMessage : virtual public ASentPacket {
public:
    explicit ExchangeBidHouseSearchMessage(const char *packet);

    ~ExchangeBidHouseSearchMessage() override = default;

    [[nodiscard]] std::string dump() const override;

    friend std::ostream &operator<<(std::ostream &os, const ExchangeBidHouseSearchMessage &packet);

private:
    uint16_t m_packet_id = 8231;
    uint32_t m_object_id;
    bool m_follow;
};

#endif //DOFUS_TEST_EXCHANGEBIDHOUSESEARCHMESSAGE_HPP
