//
// Created by lou on 01/05/2024.
//

#include <iostream>
#include <string>
#include "ObjectItem.hpp"
#include "Utils.hpp"

ObjectItem::ObjectItem(const char *buffer, std::size_t &pos) {
    m_position = buffer[pos] << 8 | buffer[pos + 1];
    pos += 2;
    m_gid = Utils::readVarUInt(buffer, pos);
    m_nb_effects = buffer[pos] << 8 | buffer[pos + 1];
    pos += 2;
    int i = 0;
    for (; i < m_nb_effects; i += 2) {
        uint16_t effect_id = buffer[pos + i] << 8 | buffer[pos + i + 1];
        m_effects.emplace_back(effect_id);
    }
    pos += i;
    m_uid = Utils::readVarUInt(buffer, pos);
    m_quantity = Utils::readVarUInt(buffer, pos);
    m_favorite = buffer[pos];
    ++pos;
}

std::string ObjectItem::dump() const {
    return "ObjectItem{pos: " + std::to_string(m_position) + "; nb_effects: " + std::to_string(m_nb_effects) + "; gid: " + std::to_string(m_gid) +
           "; quantity: " + std::to_string(m_quantity) + "}";
}
