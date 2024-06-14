#ifndef PLAYER_PLAYERMAPINPUT_HPP
#define PLAYER_PLAYERMAPINPUT_HPP

#include "EventSystem/MapSystem.hpp"
#include <memory>
namespace Player {
class PlayerMapInput {
public:
    PlayerMapInput(const std::shared_ptr<EventSystem::MapSystem>& map);
    void InputUpdate();
private:
    std::shared_ptr<EventSystem::MapSystem> m_Map;
};
} // namespace Player

#endif
