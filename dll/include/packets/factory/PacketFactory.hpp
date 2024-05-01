//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_PACKETFACTORY_HPP
#define DOFUS_TEST_PACKETFACTORY_HPP


#include <memory>
#include "packets/APacket.hpp"
#include "packets/impl/MapMovementPacket.hpp"
#include "packets/impl/BasicPongPacket.hpp"
#include "packets/impl/ChatMessagePacket.hpp"
#include "packets/impl/PlayerInventoryPacket.hpp"
#include "packets/impl/BasicPingPacket.hpp"
#include "packets/impl/BasicAckPacket.hpp"
#include "packets/impl/GameContextRemoveElementPacket.hpp"
#include "packets/impl/NoMovementPacket.hpp"
#include "packets/impl/MapFightCountPacket.hpp"
#include "packets/impl/MultiTabStoragePacket.hpp"
#include "packets/impl/UnknownPacket.hpp"

class PacketFactory {
public:
    static std::unique_ptr<IPacket> make_packet(const char *buffer) {
        uint16_t header = (uint8_t) buffer[0] << 8 | (uint8_t) buffer[1];
        uint16_t packet_id = header >> 2;
        switch (static_cast<PacketIds>(packet_id)) {
            case PacketIds::MapMovement:
                return std::unique_ptr<IPacket>(new MapMovementPacket(buffer));
            case PacketIds::Pong:
                return std::unique_ptr<IPacket>(new BasicPongPacket(buffer));
            case PacketIds::ChatMessage:
                return std::unique_ptr<IPacket>(new ChatMessagePacket(buffer));
            case PacketIds::PlayerInventory:
                return std::unique_ptr<IPacket>(new PlayerInventoryPacket(buffer));
            case PacketIds::Ping:
                return std::unique_ptr<IPacket>(new BasicPingPacket(buffer));
            case PacketIds::BasicAck:
                return std::unique_ptr<IPacket>(new BasicAckPacket(buffer));
            case PacketIds::GameContextRemoveElement:
                return std::unique_ptr<IPacket>(new GameContextRemoveElementPacket(buffer));
            case PacketIds::MapNoMovement:
                return std::unique_ptr<IPacket>(new NoMovementPacket(buffer));
            case PacketIds::MapFightCount:
                return std::unique_ptr<IPacket>(new MapFightCountPacket(buffer));
            case PacketIds::MultiTabStorage:
                return std::unique_ptr<IPacket>(new MultiTabStoragePacket(buffer));
            default:
                return std::unique_ptr<IPacket>(new UnknownPacket(buffer));
        }
    }
};


#endif //DOFUS_TEST_PACKETFACTORY_HPP
