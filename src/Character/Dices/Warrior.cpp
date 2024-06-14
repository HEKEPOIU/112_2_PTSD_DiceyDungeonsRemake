#include "Character/Dices/Warrior.hpp"
#include "EventSystem/BattleSystem.hpp"

namespace Character::Dices {

Warrior::Warrior(const std::string &name, int level, int maxHp, int currentHp,
                 const std::string &path, const std::string &levelImagePath)
    : PlayerDice(name, level, maxHp, currentHp, path, levelImagePath) {
    m_BattleCards->AddCardById(1);
    m_BattleCards->AddCardById(-1);
}

void Warrior::RoundStart(EventSystem::BattleSystem &currentBattle) {
    BaseCharacter::RoundStart(currentBattle);
    for (int i = 0; i < m_DicesPerLevel[m_Level - 1]; i++) {
        currentBattle.RollDice();
    }
}
} // namespace Character::Dices
