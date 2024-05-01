//
// Created by lou on 01/05/2024.
//

#include <iostream>
#include "ObjectItem.hpp"
#include "Utils.hpp"

ObjectItem::ObjectItem(const char *buffer, std::size_t &pos) {
    m_position = buffer[pos] << 8 | buffer[pos + 1];
    pos += 2;
    std::cout << "item at pos: " << m_position << std::endl;
    m_gid = Utils::readVarUInt(buffer, pos);
    m_nb_effects = buffer[pos] << 8 | buffer[pos + 1];
    pos += 2;
    std::cout << "nb effects: " << m_nb_effects << std::endl;
//    for (int i = 0; i < m_nb_effects; ++i) {
//        uint16_t effect_id = buffer[pos + i] << 8 | buffer[pos + i + 1];
//        std::cout << "effect id: " << effect_id << std::endl;
////        m_effects.emplace_back(effect_id);
//    }
    m_uid = Utils::readVarUInt(buffer, pos);
    m_quantity = Utils::readVarUInt(buffer, pos);
    m_favorite = buffer[pos];
}
