#ifndef CHARACTER_ENEMYS_Pirate_HPP
#define CHARACTER_ENEMYS_Pirate_HPP

#include "Character/Enemy.hpp"
#include "ResourceConfig.hpp"
namespace Character::Enemys {
class Pirate : public Character::Enemy {
public:
    Pirate()
        : Character::Enemy("Pirate", 2, 2, 26, 26,
                           ENEMY_DIR + "/pirate/static_1080.png",
                           ENEMY_DIR + "/pirate/static_1080.png") {
        m_BattleCards->AddCardById(21);
    };
};
} // namespace Character::Enemys
#endif
