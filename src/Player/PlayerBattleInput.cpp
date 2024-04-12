#include "Player/PlayerBattleInput.hpp"
#include "EventSystem/BattleSystem.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

namespace Player {

void PlayerBattleInput::InputUpdate(EventSystem::BattleSystem &context) {
    if (!m_DiceOnHand.expired()) {
        m_DiceOnHand.lock()->SetPosition(Util::Input::GetCursorPosition());
        if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
            context.UseDice();
            m_DiceOnHand.reset();
        }
    } else {
        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
            auto currentCursorPos = Util::Input::GetCursorPosition();
            for (auto dice : context.GetPlayer().second) {
                if (dice->IsOnTop(currentCursorPos)) {
                    m_DiceOnHand = dice;
                    return;
                }
            }
            context.DetectUiClick(currentCursorPos);
        }
    }
}
} // namespace Player
