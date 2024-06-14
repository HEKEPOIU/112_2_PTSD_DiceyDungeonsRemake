#ifndef GAMECORE_MAINGAME_HPP
#define GAMECORE_MAINGAME_HPP

#include "Character/Enemy.hpp"
#include "Character/PlayerDice.hpp"
#include "EventSystem/BaseEventSystem.hpp"
#include "Util/GameObject.hpp"
#include <memory>
#include <queue>

namespace GameCore{
    class GameManager; 
    enum class GameStates;
}

namespace GameCore {
class MainGame : public Util::GameObject {
public:
    MainGame(GameManager& context, std::shared_ptr<Character::PlayerDice> &playerDice);
    void SetCurrentEvent(
        const std::shared_ptr<EventSystem::BaseEventSystem> &targetEvent);
    void
    AppendEvnet(const std::shared_ptr<EventSystem::BaseEventSystem> &event);
    void Update();

    std::shared_ptr<Character::PlayerDice> &GetPlayerDice() {
        return m_PlayerDice;
    }
    void EndGame();

    void ChangeGameState(GameStates newState);

    void EndEvent();

private:
    std::shared_ptr<EventSystem::BaseEventSystem> m_CurrentEvent;
    std::shared_ptr<Character::PlayerDice> m_PlayerDice;
    std::shared_ptr<Character::Enemy> m_Enemy;
    std::queue<std::shared_ptr<EventSystem::BaseEventSystem>> m_EventQueue;
    GameManager& m_Context;
};
} // namespace GameCore

#endif
