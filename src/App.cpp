#include "App.hpp"

#include "DiceUtils/Dice.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include <memory>

void App::Start() {
    LOG_TRACE("Start");
    m_Dice = std::make_shared<DiceUtils::Dice>(6);
    m_CurrentState = State::UPDATE;
}

void App::Update() {

    // TODO: do your things here and delete this line <3

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    m_Dice->Draw();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
