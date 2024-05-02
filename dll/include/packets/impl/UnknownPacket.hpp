//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_UNKNOWNPACKET_HPP
#define DOFUS_TEST_UNKNOWNPACKET_HPP

#include <ostream>
#include "packets/AReceivedPacket.hpp"

class UnknownPacket : virtual public AReceivedPacket {
public:
    explicit UnknownPacket(const char *packet);

    ~UnknownPacket() override = default;

    [[nodiscard]] std::string dump() const override;
    friend std::ostream &operator<<(std::ostream &os, const UnknownPacket &packet);

private:
};

#endif //DOFUS_TEST_UNKNOWNPACKET_HPP
