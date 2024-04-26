#ifndef GAMECORE_MAINGAME_HPP
#define GAMECORE_MAINGAME_HPP

#include "Character/PlayerDice.hpp"
#include "EventSystem/BaseEventSystem.hpp"
#include "Util/GameObject.hpp"
#include <memory>
namespace GameCore {
class MainGame : public Util::GameObject {
public:
    MainGame(std::shared_ptr<EventSystem::BaseEventSystem> startEvent);
    void
    SetCurrentEvent(std::shared_ptr<EventSystem::BaseEventSystem> targetEvent);
    void OnGameStatesChange(
        std::shared_ptr<EventSystem::BaseEventSystem> m_CurrentEvent);
    void Update();

private:
    std::shared_ptr<EventSystem::BaseEventSystem> m_CurrentEvent;
    std::shared_ptr<Character::PlayerDice> m_PlayerDice;
};
} // namespace GameCore

#endif
