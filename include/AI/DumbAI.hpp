#ifndef AI_DUMBAI_HPP
#define AI_DUMBAI_HPP

#include "AI/EnemyAI.hpp"
namespace AI {
class DumbAI : public EnemyAI {
public:
    DumbAI() = default;
    void RoundUpdate(EventSystem::BattleSystem &currentBattle) override;
};
} // namespace AI

#endif
