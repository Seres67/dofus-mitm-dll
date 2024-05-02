//
// Created by lou on 02/05/2024.
//

#ifndef DOFUS_TEST_OBJECTEFFECT_HPP
#define DOFUS_TEST_OBJECTEFFECT_HPP


#include <cstdint>

class ObjectEffect {
public:
    explicit ObjectEffect(const char *buffer);
    explicit ObjectEffect(uint16_t effect_id);

private:
    uint16_t m_effect_id;
};


#endif //DOFUS_TEST_OBJECTEFFECT_HPP
