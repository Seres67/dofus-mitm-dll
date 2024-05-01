//
// Created by lou on 01/05/2024.
//

#ifndef DOFUS_TEST_OBJECTITEM_HPP
#define DOFUS_TEST_OBJECTITEM_HPP


#include <vector>
#include <cstdint>
#include "ObjectEffect.hpp"

class ObjectItem {
public:
    explicit ObjectItem(const char *buffer, std::size_t &pos);
private:
    uint16_t m_position;
    uint32_t m_gid;
    uint16_t m_nb_effects;
    std::vector<ObjectEffect> m_effects;
    uint32_t m_uid;
    uint32_t m_quantity;
    bool m_favorite;
};


#endif //DOFUS_TEST_OBJECTITEM_HPP
