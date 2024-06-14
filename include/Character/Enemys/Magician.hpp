#ifndef CHARACTER_ENEMYS_Magician_HPP
#define CHARACTER_ENEMYS_Magician_HPP

#include "Character/Enemy.hpp"
#include "ResourceConfig.hpp"
namespace Character::Enemys {
class Magician : public Character::Enemy {
public:
    Magician()
        : Character::Enemy("Magician", 1, 1, 9, 9,
                           ENEMY_DIR + "/streetmagician/static_1080.png",
                           ENEMY_DIR + "/streetmagician/static_1080.png") {
        m_BattleCards->AddCardById(19);
        m_BattleCards->AddCardById(20);
    };
};
} // namespace Character::Enemys
#endif
