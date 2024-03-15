#include "GameCore/GameManager.hpp"
#include <stdexcept>

namespace GameCore {
GameManager::GameManager(GameStates startState)
    : m_CurrentStates(startState) {}

void GameManager::UpdateGame() {
    switch (m_CurrentStates) {
    case GameStates::TITLESTATE:
        // TODO: Implement TitleUI And StartUp Logic.
        throw std::logic_error("TITLESTATE states not yet implemented");
    case GameStates::CHARACTERSELECT:
        // TODO: Implement CHARACTERSELECT And inject to MainGame.
        throw std::logic_error("CHARACTERSELECT states not yet implemented");
    case GameStates::MAINGAME:
        throw std::logic_error("CHARACTERSELECT states not yet implemented");
    }
}

} // namespace GameCore
