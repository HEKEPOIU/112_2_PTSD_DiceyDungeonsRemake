#include "GameCore/MainGame.hpp"
#include "Character/Enemys/EnemyFactory.hpp"
#include "EventSystem/MapSystem.hpp"
#include <memory>

namespace GameCore {
MainGame::MainGame(std::shared_ptr<Character::PlayerDice> &playerDice)
    : m_PlayerDice(playerDice) {
    m_Enemy = Character::Enemys::EnemyFactory::CreateEnemy(1);
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
    OnGameStatesChange(m_CurrentEvent);
}
void MainGame::Update() {
    m_CurrentEvent->EventUpdate();
}

void MainGame::OnGameStatesChange(
    const std::shared_ptr<EventSystem::BaseEventSystem> &currentEvent) {}

} // namespace GameCore
