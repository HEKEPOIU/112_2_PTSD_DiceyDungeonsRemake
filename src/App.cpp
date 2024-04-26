#include "App.hpp"

#include "Character/Dices/Warrior.hpp"
#include "Character/Enemys/Frog.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include <memory>

void App::Start() {
    LOG_TRACE("Start");
    m_CurrentState = State::UPDATE;
    // m_PlayerDice = std::make_shared<Character::Dices::Warrior>(
    //     "Thief", 1, 24, 24,
    //     RESOURCE_DIR "/graphics/characters/thief/static_1080.png");
    // m_TestEnemy = std::make_shared<Character::Enemys::Frog>();

    // m_BattleSystem = std::make_shared<EventSystem::BattleSystem>(
    //     nullptr, m_PlayerDice, m_TestEnemy);

    // m_BattleSystem->AddChild(m_PlayerDice);
    // m_BattleSystem->AddChild(m_TestEnemy);
    m_MainGame = std::make_shared<GameCore::MainGame>(nullptr);
    m_Root->AddChild(m_MainGame);
}

void App::Update() {

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    m_Root->Update();
    m_MainGame->Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    // Display fps
    // LOG_ERROR(fmt::format("{:.02f}", 1.0F / Util::Time::GetDeltaTime()));
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
