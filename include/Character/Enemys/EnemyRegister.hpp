#ifndef CHARACTER_ENEMYS_ENEMYREGISTER_HPP
#define CHARACTER_ENEMYS_ENEMYREGISTER_HPP

#include "Character/Enemys/EnemyFactory.hpp"
#include "Character/Enemys/Frog.hpp"

namespace Character::Enemys {
class EnemyRegister {
public:
    EnemyRegister() {
        // Register card, should it put in constructor?
        EnemyFactory::RegisterEnemy(1, [] { return std::make_shared<Frog>(); });
    }
};
} // namespace Character::Enemys

#endif
