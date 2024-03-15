#ifndef CHARACTER_ENEMY_HPP
#define CHARACTER_ENEMY_HPP

#include "AI/EnemyAI.hpp"
#include "Character/BaseCharacter.hpp"
#include <memory>
namespace Character {
class Enemy : public BaseCharacter {
public:
    Enemy(int level, int maxHp, int currentHp, const std::string &path);

    virtual void RoundStart(EventSystem::BattleSystem &currentBattle) override;
    virtual void RoundUpdate(EventSystem::BattleSystem &currentBattle) override;
    virtual void RoundEnd(EventSystem::BattleSystem &currentBattle) override;
    virtual void SetBattlePosition() override;

private:
    std::unique_ptr<AI::EnemyAI> m_AIBrain{};
};
} // namespace Character

#endif
