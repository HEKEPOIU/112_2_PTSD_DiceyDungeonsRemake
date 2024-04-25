#include "AI/DumbAI.hpp"
#include "AI/EnemyAI.hpp"
#include "Util/Logger.hpp"

namespace AI {
void DumbAI::RoundUpdate(EventSystem::BattleSystem &currentBattle) {
    EnemyAI::RoundUpdate(currentBattle);
    // If no Card left, or no dice left, end the turn.

    if (currentBattle.GetEnemy().second.size() == 0) {
        currentBattle.ChangeStates();
        return;
    }
    if (isWaiting) {
        return;
    }

    auto card = GetAvailableCard(currentBattle);

    if (card.first == nullptr) {
        currentBattle.ChangeStates();
        return;
    }
    LOG_ERROR("Find Card");
    UseDice(card.first, card.second, currentBattle);

    StartDelay();
}

} // namespace AI
