#include "Character/Enemy.hpp"
#include "Character/BaseCharacter.hpp"
#include "EventSystem/BattleSystem.hpp"
#include "Util/Logger.hpp"

namespace Character {

Enemy::Enemy(const std::string &name, int initDiceCount, int level, int maxHp,
             int currentHp, const std::string &path)
    : BaseCharacter(name, level, maxHp, currentHp, path),
      diceCount(initDiceCount) {}

void Enemy::RoundStart(EventSystem::BattleSystem &currentBattle) {
    BaseCharacter::RoundStart(currentBattle);
    for (int i = 0; i < diceCount; i++) {
        LOG_ERROR("Enemy Roll Dice");
        currentBattle.RollDice();
    }
};
void Enemy::RoundUpdate(EventSystem::BattleSystem &currentBattle){

};
void Enemy::RoundEnd(EventSystem::BattleSystem &currentBattle){

};
void Enemy::SetBattlePosition() {
    m_Transform.translation = {750, 400};
    m_Transform.scale = {1.f, 1.f};
}
} // namespace Character
