#ifndef GAMECORE_MAINGAME_HPP
#define GAMECORE_MAINGAME_HPP

#include "EventSystem/BaseEventSystem.hpp"
#include <memory>
namespace GameCore {
class MainGame {
public:
    MainGame(std::shared_ptr<EventSystem::BaseEventSystem> startEvent);
    void
    SetCurrentEvent(std::shared_ptr<EventSystem::BaseEventSystem> targetEvent);
    void OnGameStatesChange(
        std::shared_ptr<EventSystem::BaseEventSystem> m_CurrentEvent);

private:
    std::shared_ptr<EventSystem::BaseEventSystem> m_CurrentEvent;
};
} // namespace GameCore

#endif
