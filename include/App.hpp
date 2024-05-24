#ifndef APP_HPP
#define APP_HPP

#include "Cards/CardRegister.hpp"
#include "Character/Enemys/EnemyRegister.hpp"
#include "GameCore/GameManager.hpp"
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

    void EndGame() { m_CurrentState = State::END; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    State m_CurrentState = State::START;
    std::shared_ptr<GameCore::GameManager> m_GameManager;
    std::unique_ptr<Util::Renderer> m_Root = std::make_unique<Util::Renderer>();
    std::unique_ptr<Cards::CardRegister> m_CardRegister =
        std::make_unique<Cards::CardRegister>();
    std::unique_ptr<Character::Enemys::EnemyRegister> m_EnemyRegister =
        std::make_unique<Character::Enemys::EnemyRegister>();
};

#endif
