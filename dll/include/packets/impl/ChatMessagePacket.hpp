//
// Created by lou on 30/04/2024.
//

#ifndef DOFUS_TEST_CHATMESSAGEPACKET_HPP
#define DOFUS_TEST_CHATMESSAGEPACKET_HPP


#include <cstdint>
#include <ostream>
#include "packets/APacket.hpp"

class ChatMessagePacket : virtual public APacket {
public:
    explicit ChatMessagePacket(const char *packet);

    ~ChatMessagePacket() override = default;

    friend std::ostream &operator<<(std::ostream &os, const ChatMessagePacket &packet);

    std::string dump() const override;

private:
    uint16_t m_packet_id = 1304;
    uint8_t m_channel;
    uint16_t m_message_size;
    std::string m_message_content;
    uint32_t m_timestamp;
    uint16_t m_fingerprint_size;
    uint64_t m_fingerprint = 0;
    uint64_t m_sender_id = 0;
    uint16_t m_sender_name_size;
    std::string m_sender_name;
    uint16_t m_prefix_name_size;
    uint32_t m_sender_account_id;
};


#endif //DOFUS_TEST_CHATMESSAGEPACKET_HPP
