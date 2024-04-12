#ifndef PLAYER_PLAYERBATTLEINPUT_HPP
#define PLAYER_PLAYERBATTLEINPUT_HPP

#include "DiceUtils/Dice.hpp"
#include <memory>
namespace EventSystem {
class BattleSystem;
} // namespace EventSystem

namespace Player {
class PlayerBattleInput {
public:
    PlayerBattleInput() = default;
    void InputUpdate(EventSystem::BattleSystem &context);

private:
    std::weak_ptr<DiceUtils::Dice> m_DiceOnHand;
};
} // namespace Player

#endif
