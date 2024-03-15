#include "Character/PlayerDice.hpp"
#include "Character/BaseCharacter.hpp"
#include "EventSystem/BattleSystem.hpp"
#include "Util/Logger.hpp"

namespace Character {
PlayerDice::PlayerDice(int level, int maxHp, int currentHp,
                       const std::string &path)
    : BaseCharacter(level, maxHp, currentHp, path) {}

void PlayerDice::RoundStart(EventSystem::BattleSystem &currentBattle){};
void PlayerDice::RoundUpdate(EventSystem::BattleSystem &currentBattle){};
void PlayerDice::RoundEnd(EventSystem::BattleSystem &currentBattle){};

void PlayerDice::SetBattlePosition() {
    m_Transform.translation = {-750, -400};
    m_Transform.scale = {2.f, 2.f};
}
} // namespace Character
