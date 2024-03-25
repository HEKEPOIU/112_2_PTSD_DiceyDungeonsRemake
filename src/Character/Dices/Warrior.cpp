#include "Character/Dices/Warrior.hpp"
#include "EventSystem/BattleSystem.hpp"
#include "Util/Logger.hpp"

namespace Character::Dices {

void Warrior::RoundStart(EventSystem::BattleSystem &currentBattle) {
    BaseCharacter::RoundStart(currentBattle);
    for (int i = 0; i < m_DicesPerLevel[m_Level - 1]; i++) {
        currentBattle.RollDice();
    }
}
} // namespace Character::Dices
