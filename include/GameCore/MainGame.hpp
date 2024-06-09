#ifndef GAMECORE_MAINGAME_HPP
#define GAMECORE_MAINGAME_HPP

#include "Character/Enemy.hpp"
#include "Character/PlayerDice.hpp"
#include "EventSystem/BaseEventSystem.hpp"
#include "Util/GameObject.hpp"
#include <memory>
namespace GameCore {
class MainGame : public Util::GameObject {
public:
    MainGame(std::shared_ptr<Character::PlayerDice> &playerDice);
    void SetCurrentEvent(
        const std::shared_ptr<EventSystem::BaseEventSystem> &targetEvent);
    void OnGameStatesChange(
        const std::shared_ptr<EventSystem::BaseEventSystem> &currentEvent);
    void Update();

    std::shared_ptr<Character::PlayerDice> &GetPlayerDice() {
        return m_PlayerDice;
    }

private:
    std::shared_ptr<EventSystem::BaseEventSystem> m_CurrentEvent;
    std::shared_ptr<Character::PlayerDice> m_PlayerDice;
    std::shared_ptr<Character::Enemy> m_Enemy;
};
} // namespace GameCore

#endif
