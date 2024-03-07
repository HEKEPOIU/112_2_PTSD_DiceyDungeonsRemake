#ifndef CHARACTER_ENEMY_HPP
#define CHARACTER_ENEMY_HPP

#include "AI/EnemyAI.hpp"
#include "Character/BaseCharacter.hpp"
#include <memory>
namespace Character {
class Enemy : public BaseCharacter {

private:
    std::unique_ptr<AI::EnemyAI> m_AIBrain;
};
} // namespace Character

#endif
