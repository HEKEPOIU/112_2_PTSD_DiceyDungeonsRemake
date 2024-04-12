#include "Character/Enemys/Frog.hpp"
#include "ResourceConfig.hpp"

namespace Character::Enemys {
Frog::Frog()
    : Enemy("frog", 2, 1, 9, 9, ENEMY_DIR + "/frog/static_1080.png") {
    m_BattleCards->AddCardById(2);
    m_BattleCards->AddCardById(3);
}
} // namespace Character::Enemys
