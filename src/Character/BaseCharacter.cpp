#include "Character/BaseCharacter.hpp"
#include "Character/HealthSystem.hpp"
#include "Util/Image.hpp"
#include <glm/fwd.hpp>
#include <glm/gtx/string_cast.hpp>
#include <memory>

namespace Character {

BaseCharacter::BaseCharacter(const std::string &name, int level, int maxHp,
                             int currentHp, const std::string &path, const std::string &levelImagePath)
    : m_Name(name),
      m_CharacterImage(std::make_shared<Util::Image>(path)),
      m_HealthSystem(std::make_unique<HealthSystem>(maxHp, currentHp)),
      m_LevelImage(std::make_shared<Util::Image>(levelImagePath)),
      m_Level(level) {
    SetDrawable(m_CharacterImage);
}

void BaseCharacter::BindOnCurrentHealthChange(
    const std::string &eventId,
    std::function<void(int, int)> onCurrentHealthChange) {
    m_HealthSystem->BindOnCurrentHealthChange(eventId, onCurrentHealthChange);
}

void BaseCharacter::BindOnMaxHealthChange(
    const std::string &eventId,
    std::function<void(int, int)> onMaxHealthChange) {
    m_HealthSystem->BindOnMaxHealthChange(eventId, onMaxHealthChange);
}

void BaseCharacter::UnBindOnCurrentHealthChange(const std::string &eventId) {
    m_HealthSystem->UnBindOnCurrentHealthChange(eventId);
}

void BaseCharacter::UnBindOnMaxHealthChange(const std::string &eventId) {
    m_HealthSystem->UnBindOnMaxHealthChange(eventId);
}

void BaseCharacter::RoundStart(EventSystem::BattleSystem &currentBattle) {
    m_HealthSystem->SetCurrentHealth(m_HealthSystem->GetCurrentHealth());
    m_HealthSystem->SetMaxHealth(m_HealthSystem->GetMaxHealth());
    // m_BattleCards
}
void BaseCharacter::RoundUpdate(EventSystem::BattleSystem &currentBattle) {}
void BaseCharacter::RoundEnd(EventSystem::BattleSystem &currentBattle) {}

} // namespace Character
