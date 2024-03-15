#include "EventSystem/BaseEventSystem.hpp"
#include "GameCore/MainGame.hpp"

namespace EventSystem {
BaseEventSystem::BaseEventSystem(std::shared_ptr<GameCore::MainGame> mainGame)
    : m_MainGame(mainGame) {}
} // namespace EventSystem
