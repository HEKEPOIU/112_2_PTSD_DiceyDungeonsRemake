#include "Character/Enemy.hpp"
#include "Character/BaseCharacter.hpp"
#include "EventSystem/BattleSystem.hpp"

namespace Character {

Enemy::Enemy(int level, int maxHp, int currentHp, const std::string &path)
    : BaseCharacter(level, maxHp, currentHp, path) {}

void Enemy::RoundStart(EventSystem::BattleSystem &currentBattle){

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
