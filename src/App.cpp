#include "App.hpp"

#include "GameCore/GameManager.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include <memory>

void App::Start() {
    LOG_TRACE("Start");
    m_CurrentState = State::UPDATE;
    m_GameManager = std::make_shared<GameCore::GameManager>(
        *this, GameCore::GameStates::TITLESTATE);
    m_Root->AddChild(m_GameManager);
}

void App::Update() {

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    m_Root->Update();
    m_GameManager->UpdateGame();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
