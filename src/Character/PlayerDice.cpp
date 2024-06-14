#include "Character/PlayerDice.hpp"
#include "Character/BaseCharacter.hpp"
#include "EventSystem/BattleSystem.hpp"

namespace Character {
PlayerDice::PlayerDice(const std::string &name, int level, int maxHp,
                       int currentHp, const std::string &path,
                       const std::string &levelImagePath)
    : BaseCharacter(name, level, maxHp, currentHp, path, levelImagePath) {}

void PlayerDice::RoundStart(EventSystem::BattleSystem &currentBattle) {
    BaseCharacter::RoundStart(currentBattle);
};
void PlayerDice::RoundUpdate(EventSystem::BattleSystem &currentBattle) {
    BaseCharacter::RoundUpdate(currentBattle);
};
void PlayerDice::RoundEnd(EventSystem::BattleSystem &currentBattle) {
    BaseCharacter::RoundEnd(currentBattle);
};

void PlayerDice::SetBattlePosition() {
    m_Transform.translation = {-800, -350};
    m_Transform.scale = {1.f, 1.f};
}

void PlayerDice::SetExp(int newExp) {
    m_CurrentExp = newExp;
    int currentLevelUpArr = GetCurrentLevelUpArr();
    if (m_CurrentExp >= currentLevelUpArr) {
        m_Level++;
        m_CurrentExp -= currentLevelUpArr;
        SetMaxHealth(m_HpPerLevel[m_Level-1]);
        SetCurrentHealth(m_HpPerLevel[m_Level-1]);
    }
};
} // namespace Character
