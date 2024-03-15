#include "Character/Dices/Thief.hpp"
#include "EventSystem/BattleSystem.hpp"
#include "Util/Logger.hpp"

namespace Character::Dices {

void Thief::RoundStart(EventSystem::BattleSystem &currentBattle) {
    LOG_ERROR(m_Level);
    for (int i = 0; i < m_DicesPerLevel[m_Level - 1]; i++) {
        currentBattle.RollDice();
    }
}
} // namespace Character::Dices
