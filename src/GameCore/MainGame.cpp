#include "GameCore/MainGame.hpp"
#include "EventSystem/BaseEventSystem.hpp"
#include "EventSystem/EndSystem.hpp"
#include "EventSystem/MapSystem.hpp"
#include <memory>
#include "GameCore/GameManager.hpp"

namespace GameCore {
MainGame::MainGame(GameManager &context,
                   std::shared_ptr<Character::PlayerDice> &playerDice)
    : m_PlayerDice(playerDice),
      m_Context(context) {
    SetCurrentEvent(std::make_shared<EventSystem::MapSystem>(*this));
}

void MainGame::SetCurrentEvent(
    const std::shared_ptr<EventSystem::BaseEventSystem> &targetEvent) {
    if (m_CurrentEvent.get() == targetEvent.get()) {
        return;
    }
    if (m_CurrentEvent != nullptr) {
        m_CurrentEvent->EventEnd();
        RemoveChild(m_CurrentEvent);
    }

    m_CurrentEvent = targetEvent;
    m_CurrentEvent->EventStart();
    AddChild(m_CurrentEvent);
}
void MainGame::AppendEvnet(
    const std::shared_ptr<EventSystem::BaseEventSystem> &targetEvend) {
    m_EventQueue.push(targetEvend);
}
void MainGame::EndEvent() {
    auto event = m_EventQueue.front();
    SetCurrentEvent(event);
    m_EventQueue.pop();
}
void MainGame::Update() {
    m_CurrentEvent->EventUpdate();
}

void MainGame::ChangeGameState(GameStates newState){
    RemoveChild(m_CurrentEvent);
    m_Context.ChangeStates(newState);
}

void MainGame::EndGame(){
    m_Context.EndGame();
}

} // namespace GameCore
