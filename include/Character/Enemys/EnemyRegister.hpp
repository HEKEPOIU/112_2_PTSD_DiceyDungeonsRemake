#ifndef CHARACTER_ENEMYS_ENEMYREGISTER_HPP
#define CHARACTER_ENEMYS_ENEMYREGISTER_HPP

#include "Character/Enemys/EnemyFactory.hpp"
#include "Character/Enemys/Frog.hpp"
#include "Character/Enemys/Magician.hpp"
#include "Character/Enemys/Pirate.hpp"

namespace Character::Enemys {
class EnemyRegister {
public:
    EnemyRegister() {
        // Register card, should it put in constructor?
        EnemyFactory::RegisterEnemy(1, [] { return std::make_shared<Frog>(); });
        EnemyFactory::RegisterEnemy(
            2, [] { return std::make_shared<Magician>(); });
        EnemyFactory::RegisterEnemy(3,
                                    [] { return std::make_shared<Pirate>(); });
    }
};
} // namespace Character::Enemys

#endif
