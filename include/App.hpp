#ifndef APP_HPP
#define APP_HPP

#include "Character/Dices/Thief.hpp"
#include "Character/Enemy.hpp"
#include "EventSystem/BattleSystem.hpp"
#include "Util/Root.hpp"
#include "pch.hpp" // IWYU pragma: export
#include <memory>

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    State m_CurrentState = State::START;
    std::shared_ptr<Character::Dices::Thief> m_PlayerDice;
    std::shared_ptr<Character::Enemy> m_TestEnemy;
    std::shared_ptr<EventSystem::BattleSystem> m_BattleSystem;
    std::unique_ptr<Util::Root> m_Root = std::make_unique<Util::Root>();
};

#endif
