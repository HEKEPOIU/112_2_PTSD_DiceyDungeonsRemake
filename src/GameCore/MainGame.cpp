#include "GameCore/MainGame.hpp"

namespace GameCore {
MainGame::MainGame(std::shared_ptr<EventSystem::BaseEventSystem> startEvent)
    : m_CurrentEvent(startEvent) {}

void MainGame::SetCurrentEvent(
    std::shared_ptr<EventSystem::BaseEventSystem> targetEvent) {
    if (m_CurrentEvent.get() == targetEvent.get()) {
        return;
    }
    m_CurrentEvent = targetEvent;
    OnGameStatesChange(m_CurrentEvent);
}

void MainGame::OnGameStatesChange(
    std::shared_ptr<EventSystem::BaseEventSystem> m_CurrentEvent) {}

} // namespace GameCore
