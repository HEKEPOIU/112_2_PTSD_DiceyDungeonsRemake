#include "Player/PlayerBattleInput.hpp"
#include "EventSystem/BattleSystem.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

namespace Player {

void PlayerBattleInput::InputUpdate(EventSystem::BattleSystem &context) {
    if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
        auto currentCursorPos = Util::Input::GetCursorPosition();
        for (auto dice : context.GetPlayer().second) {
            if (dice->IsOnTop(currentCursorPos)) {
                dice->SetPosition(currentCursorPos);
                break;
            }
        }
    }
}
} // namespace Player
