#ifndef EVENTSYSTEM_MAPSYSTEM_HPP
#define EVENTSYSTEM_MAPSYSTEM_HPP

#include "GameCore/MainGame.hpp"
namespace EventSystem {
class MapSystem : public BaseEventSystem {
public:
    MapSystem(GameCore::MainGame &mainGame);
    void EventStart() override;
    void EventUpdate() override;
    void EventEnd() override;
};
} // namespace EventSystem

#endif
