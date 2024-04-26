#include "GameCore/MainGame.hpp"
#include "Character/Dices/Warrior.hpp"
#include "Character/Enemys/EnemyFactory.hpp"
#include "Util/Logger.hpp"
#include <memory>

namespace GameCore {
MainGame::MainGame() {
    m_PlayerDice = std::make_shared<Character::Dices::Warrior>(
        "Thief", 1, 24, 24,
        RESOURCE_DIR "/graphics/characters/thief/static_1080.png");
    m_Enemy = Character::Enemys::EnemyFactory::CreateEnemy(1);
    SetCurrentEvent(std::make_shared<EventSystem::BattleSystem>(
        *this, m_PlayerDice, m_Enemy));
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
