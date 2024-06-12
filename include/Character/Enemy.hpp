#ifndef CHARACTER_ENEMY_HPP
#define CHARACTER_ENEMY_HPP

#include "AI/DumbAI.hpp"
#include "AI/EnemyAI.hpp"
#include "Character/BaseCharacter.hpp"
#include <memory>
namespace Character {
class Enemy : public BaseCharacter {
public:
    Enemy(const std::string &name, int initDiceCount, int level, int maxHp,
          int currentHp, const std::string &path, const std::string &levelImagePath);

    virtual void RoundStart(EventSystem::BattleSystem &currentBattle) override;
    virtual void RoundUpdate(EventSystem::BattleSystem &currentBattle) override;
    virtual void RoundEnd(EventSystem::BattleSystem &currentBattle) override;
    virtual void SetBattlePosition() override;

protected:
    std::unique_ptr<AI::EnemyAI> m_AIBrain = std::make_unique<AI::DumbAI>();
    int diceCount;
};
} // namespace Character

#endif
