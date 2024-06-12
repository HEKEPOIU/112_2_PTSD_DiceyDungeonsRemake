#ifndef EVENTSYSTEM_MAPSYSTEM_HPP
#define EVENTSYSTEM_MAPSYSTEM_HPP

#include "EventSystem/Maps/Map.hpp"
#include "GameCore/MainGame.hpp"
#include "Player/PlayerMapInput.hpp"
#include <memory>
namespace EventSystem {
class MapSystem : public BaseEventSystem {
public:
    MapSystem(GameCore::MainGame &mainGame);
    void EventStart() override;
    void EventUpdate() override;
    void EventEnd() override;
private:
    std::shared_ptr<Maps::Map> m_Current; 
    std::shared_ptr<Player::PlayerMapInput> m_PlayerInput;
};
} // namespace EventSystem

#endif
