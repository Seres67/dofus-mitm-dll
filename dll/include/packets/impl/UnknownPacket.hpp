//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_UNKNOWNPACKET_HPP
#define DOFUS_TEST_UNKNOWNPACKET_HPP

#include <ostream>
#include "packets/APacket.hpp"

class UnknownPacket : virtual public APacket {
public:
    explicit UnknownPacket(const char *packet);

    ~UnknownPacket() override = default;

    [[nodiscard]] std::string dump() const override;
    friend std::ostream &operator<<(std::ostream &os, const UnknownPacket &packet);

private:
};

#endif //DOFUS_TEST_UNKNOWNPACKET_HPP
