#ifndef CHARACTER_PLAYERDICE_HPP
#define CHARACTER_PLAYERDICE_HPP

#include "Cards/CardSystem.hpp"
#include "Character/BaseCharacter.hpp"

namespace Character {
class PlayerDice : public BaseCharacter {

protected:
    std::unique_ptr<Cards::CardSystem> m_BagCards;
    int m_Money;
    int m_Exp;
};
} // namespace Character

#endif
