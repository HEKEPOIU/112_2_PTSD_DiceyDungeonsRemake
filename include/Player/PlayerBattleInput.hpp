#ifndef PLAYER_PLAYERBATTLEINPUT_HPP
#define PLAYER_PLAYERBATTLEINPUT_HPP

namespace EventSystem {
class BattleSystem;
} // namespace EventSystem

namespace Player {
class PlayerBattleInput {
public:
    PlayerBattleInput() = default;
    void InputUpdate(EventSystem::BattleSystem &context);
};
} // namespace Player

#endif
