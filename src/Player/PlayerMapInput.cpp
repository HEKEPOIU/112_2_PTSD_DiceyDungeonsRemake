#include "Player/PlayerMapInput.hpp"
#include "EventSystem/MapSystem.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include <memory>

namespace Player {

PlayerMapInput::PlayerMapInput(
    const std::shared_ptr<EventSystem::MapSystem> &map)
    : m_Map(map) {}

void PlayerMapInput::InputUpdate() {
    auto nodes = m_Map->GetMapNodes();
    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
        for (auto node : nodes) {
            if (node->IsOnTop(Util::Input::GetCursorPosition()) == true) {
                m_Map->MovePlayerToTarget(node);
                return;
            }
        }
    }
}
} // namespace Player
