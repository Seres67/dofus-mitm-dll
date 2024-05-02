//
// Created by lou on 02/05/2024.
//

#include "ObjectEffect.hpp"

ObjectEffect::ObjectEffect(const char *buffer) {
    m_effect_id = buffer[0] << 8 | buffer[1];
}

ObjectEffect::ObjectEffect(uint16_t effect_id) : m_effect_id(effect_id) {

}
