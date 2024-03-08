#ifndef CHARACTER_CHARACTER_HPP
#define CHARACTER_CHARACTER_HPP

#include "Cards/CardSystem.hpp"
#include "Character/HealthSystem.hpp"
#include "DiceUtils/Dice.hpp"
#include <memory>

namespace Character {
class BaseCharacter {

protected:
    std::unique_ptr<HealthSystem> m_HealthSystem;
    std::unique_ptr<Cards::CardSystem> m_BattleCards;
    std::vector<DiceUtils::Dice> m_currentDice;
    int m_Level;
};
} // namespace Character

#endif
