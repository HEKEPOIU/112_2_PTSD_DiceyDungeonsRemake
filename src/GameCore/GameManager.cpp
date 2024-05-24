#include "GameCore/GameManager.hpp"
#include "App.hpp"
#include "Util/Logger.hpp"

namespace GameCore {
GameManager::GameManager(App &context, GameStates startState)
    : m_CurrentStates(startState),
      m_Context(context) {
    m_StartUIManager = std::make_shared<UI::StartUIManager>(*this);
    OnGameStatesChange(startState, startState);
    AddChild(m_StartUIManager);
}

void GameManager::UpdateGame() {
    switch (m_CurrentStates) {
    case GameStates::TITLESTATE:
    case GameStates::CHARACTERSELECT:
        m_StartUIManager->Update();
        break;
        // TODO: Implement CHARACTERSELECT And inject to MainGame.
    case GameStates::MAINGAME:
        m_MainGame->Update();
        break;
    }
}

void GameManager::ChangeStates(GameStates newState) {
    LOG_ERROR("Change States");
    if (newState == m_CurrentStates) {
        return;
    }
    GameStates oldTemp = m_CurrentStates;
    m_CurrentStates = newState;
    OnGameStatesChange(oldTemp, m_CurrentStates);
}

void GameManager::OnGameStatesChange(GameStates oldState, GameStates newState) {
    m_StartUIManager->OnGameStatesChange(oldState, newState);
}

void GameManager::StartMainGame(Character::PlayerDice &playerDice) {
    m_CurrentStates = GameStates::MAINGAME;
    m_MainGame = std::make_shared<MainGame>();
}

void GameManager::EndGame() {
    m_Context.EndGame();
}

} // namespace GameCore
