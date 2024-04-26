#include "EventSystem/BaseEventSystem.hpp"
#include "GameCore/MainGame.hpp"

namespace EventSystem {
BaseEventSystem::BaseEventSystem(GameCore::MainGame &mainGame)
    : m_MainGame(mainGame) {}
} // namespace EventSystem
