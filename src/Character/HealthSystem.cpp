#include "Character/HealthSystem.hpp"
#include "Util/Logger.hpp"
#include <glm/common.hpp>

namespace Character {

HealthSystem::HealthSystem(int maxHp, int currentHp)
    : m_MaxHealth(maxHp),
      m_CurrentHealth(currentHp) {}

void HealthSystem::SetCurrentHealth(int value) {
    int hpTemp = m_CurrentHealth;
    int newHealth = glm::clamp(value, 0, m_MaxHealth);
    m_CurrentHealth = newHealth;
    if (!m_OnCurrentHealthChange.empty()) {
        for (auto &onCurrentHealthChange : m_OnCurrentHealthChange) {
            onCurrentHealthChange.second(hpTemp, m_CurrentHealth);
        }
    }
}
void HealthSystem::SetMaxHealth(int value) {
    if (value <= 0) {
        LOG_INFO("You Should never set the MaxHealth below 0");
        return;
    }
    int maxHpTemp = m_MaxHealth;
    m_MaxHealth = value;
    if (!m_OnMaxHealthChange.empty()) {
        for (auto &onMaxHealthChange : m_OnMaxHealthChange) {
            onMaxHealthChange.second(maxHpTemp, m_MaxHealth);
        }
    }
};
void HealthSystem::ModifyCurrentHealth(int addValue) {
    SetCurrentHealth(GetCurrentHealth() + addValue);
};

void HealthSystem::ModifyMaxHealth(int addValue) {
    SetMaxHealth(GetMaxHealth() + addValue);
}

void HealthSystem::BindOnMaxHealthChange(
    const std::string &eventId,
    std::function<void(int, int)> onMaxHealthChange) {
    auto it = m_OnMaxHealthChange.insert({eventId, onMaxHealthChange});
    if (!it.second) {
        LOG_INFO("MaxHealthChange Event:{} is already bound", eventId);
        throw std::invalid_argument("Already Bound");
    }
}

void HealthSystem::BindOnCurrentHealthChange(
    const std::string &eventId,
    std::function<void(int, int)> onCurrentHealthChange) {
    auto it = m_OnCurrentHealthChange.insert({eventId, onCurrentHealthChange});
    if (!it.second) {
        LOG_INFO("CurrentHealthChange Event:{} is already bound", eventId);
        throw std::invalid_argument("Already Bound");
    }
}

void HealthSystem::UnBindOnCurrentHealthChange(const std::string &eventId) {
    m_OnCurrentHealthChange.erase(eventId);
}

void HealthSystem::UnBindOnMaxHealthChange(const std::string &eventId) {
    m_OnMaxHealthChange.erase(eventId);
}

} // namespace Character
