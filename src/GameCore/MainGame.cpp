#include "GameCore/MainGame.hpp"
#include "Character/Dices/Warrior.hpp"
#include "Character/Enemys/EnemyFactory.hpp"
#include <memory>

namespace GameCore {
MainGame::MainGame(std::shared_ptr<EventSystem::BaseEventSystem> startEvent)
    : m_CurrentEvent(startEvent) {
    m_PlayerDice = std::make_shared<Character::Dices::Warrior>(
        "Thief", 1, 24, 24,
        RESOURCE_DIR "/graphics/characters/thief/static_1080.png");
    SetCurrentEvent(std::make_shared<EventSystem::BattleSystem>(
        std::make_shared<MainGame>(*this), m_PlayerDice,
        Character::Enemys::EnemyFactory::CreateEnemy(1)));
}

void MainGame::SetCurrentEvent(
    std::shared_ptr<EventSystem::BaseEventSystem> targetEvent) {
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
    std::shared_ptr<EventSystem::BaseEventSystem> m_CurrentEvent) {}

} // namespace GameCore
