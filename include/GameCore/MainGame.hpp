#ifndef GAMECORE_MAINGAME_HPP
#define GAMECORE_MAINGAME_HPP

#include "Character/Enemy.hpp"
#include "Character/PlayerDice.hpp"
#include "EventSystem/BaseEventSystem.hpp"
#include "Util/GameObject.hpp"
#include <memory>
#include <queue>
namespace GameCore {
class MainGame : public Util::GameObject {
public:
    MainGame(std::shared_ptr<Character::PlayerDice> &playerDice);
    void SetCurrentEvent(
        const std::shared_ptr<EventSystem::BaseEventSystem> &targetEvent);
    void
    AppendEvnet(const std::shared_ptr<EventSystem::BaseEventSystem> &event);
    void Update();

    std::shared_ptr<Character::PlayerDice> &GetPlayerDice() {
        return m_PlayerDice;
    }

    void SaveToCache(const std::shared_ptr<EventSystem::BaseEventSystem> data) {
        m_Cache = data;
    }
    
    void EndEvent();

private:
    std::shared_ptr<EventSystem::BaseEventSystem> m_CurrentEvent;
    std::shared_ptr<Character::PlayerDice> m_PlayerDice;
    std::shared_ptr<Character::Enemy> m_Enemy;
    std::queue<std::shared_ptr<EventSystem::BaseEventSystem>> m_EventQueue;
    std::shared_ptr<EventSystem::BaseEventSystem> m_Cache;
};
} // namespace GameCore

#endif
