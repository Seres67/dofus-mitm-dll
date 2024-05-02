//
// Created by lou on 02/05/2024.
//

#ifndef DOFUS_TEST_SENTPACKETNAMES_HPP
#define DOFUS_TEST_SENTPACKETNAMES_HPP

#include <string>
#include <unordered_map>
#include <cstdint>

class SentPacketNames {
public:
    static void setup_map();
    static std::string get_packet_name(uint16_t packet_id);

private:
    static std::unordered_map<uint16_t, std::string> m_packet_names;
};


#endif //DOFUS_TEST_SENTPACKETNAMES_HPP
