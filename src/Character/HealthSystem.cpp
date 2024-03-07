#include "Character/HealthSystem.hpp"
#include "Util/Logger.hpp"
#include <glm/common.hpp>

namespace Character {
void HealthSystem::SetCurrentHealth(int value) {
    int hpTemp = m_CurrentHealth;
    int newHealth = glm::clamp(value, 0, m_MaxHealth);
    m_CurrentHealth = newHealth;
    if (m_OnCurrentHealthChange) {
        m_OnCurrentHealthChange(hpTemp, newHealth);
    }
}
void HealthSystem::SetMaxHealth(int value) {
    if (value <= 0) {
        LOG_INFO("You Should never set the MaxHealth below 0");
        return;
    }
    int maxHpTemp = m_MaxHealth;
    m_MaxHealth = value;
    if (m_OnMaxHealthChange) {
        m_OnCurrentHealthChange(maxHpTemp, m_CurrentHealth);
    }
};
void HealthSystem::ModifyCurrentHealth(int addValue) {
    SetCurrentHealth(GetCurrentHealth() + addValue);
};

void HealthSystem::ModifyMaxHealth(int addValue) {
    SetMaxHealth(GetMaxHealth() + addValue);
}

} // namespace Character
