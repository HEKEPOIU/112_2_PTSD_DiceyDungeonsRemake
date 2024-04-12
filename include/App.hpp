#ifndef APP_HPP
#define APP_HPP

#include "Cards/CardRegister.hpp"
#include "Character/Dices/Warrior.hpp"
#include "Character/Enemy.hpp"
#include "EventSystem/BattleSystem.hpp"
#include "Util/Renderer.hpp"
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
    std::shared_ptr<Character::Dices::Warrior> m_PlayerDice;
    std::shared_ptr<Character::Enemy> m_TestEnemy;
    std::shared_ptr<EventSystem::BattleSystem> m_BattleSystem;
    std::unique_ptr<Util::Renderer> m_Root = std::make_unique<Util::Renderer>();
    std::unique_ptr<Cards::CardRegister> m_CardRegister =
        std::make_unique<Cards::CardRegister>();
};

#endif
