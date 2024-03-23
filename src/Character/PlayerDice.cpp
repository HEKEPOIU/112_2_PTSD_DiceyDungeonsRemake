#include "Character/PlayerDice.hpp"
#include "Character/BaseCharacter.hpp"
#include "EventSystem/BattleSystem.hpp"
#include "Util/Logger.hpp"

namespace Character {
PlayerDice::PlayerDice(const std::string &name, int level, int maxHp,
                       int currentHp, const std::string &path)
    : BaseCharacter(name, level, maxHp, currentHp, path) {}

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
} // namespace Character
