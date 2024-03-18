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
    m_Transform.translation = {-800, -350};
    m_Transform.scale = {1.f, 1.f};
}
} // namespace Character
