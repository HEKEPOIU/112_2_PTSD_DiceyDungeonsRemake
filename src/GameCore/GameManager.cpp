#include "GameCore/GameManager.hpp"
#include "App.hpp"
#include "Character/Dices/Warrior.hpp"
#include "Util/Logger.hpp"
#include <memory>

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
    if (newState == GameStates::MAINGAME) {
        StartMainGame(std::make_shared<Character::Dices::Warrior>(
            "Thief", 1, 24, 24,
            RESOURCE_DIR "/graphics/characters/thief/static_1080.png"));
        RemoveChild(m_StartUIManager);
    }
    m_StartUIManager->OnGameStatesChange(oldState, newState);
}

void GameManager::StartMainGame(
    std::shared_ptr<Character::PlayerDice> playerDice) {
    m_CurrentStates = GameStates::MAINGAME;
    m_MainGame = std::make_shared<MainGame>(playerDice);
    AddChild(m_MainGame);
}

void GameManager::EndGame() {
    m_Context.EndGame();
}

} // namespace GameCore
