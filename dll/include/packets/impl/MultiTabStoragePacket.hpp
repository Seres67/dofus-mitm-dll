//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_MULTITABSTORAGEPACKET_HPP
#define DOFUS_TEST_MULTITABSTORAGEPACKET_HPP

#include <ostream>
#include "packets/AReceivedPacket.hpp"

class MultiTabStoragePacket : virtual public AReceivedPacket {
public:
    explicit MultiTabStoragePacket(const char *packet);

    ~MultiTabStoragePacket() override = default;

    [[nodiscard]] std::string dump() const override;

    friend std::ostream &operator<<(std::ostream &os, const MultiTabStoragePacket &packet);

private:
    uint16_t m_packet_id = 3530;
};

#endif //DOFUS_TEST_MULTITABSTORAGEPACKET_HPP
