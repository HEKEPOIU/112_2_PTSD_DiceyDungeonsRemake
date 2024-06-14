#ifndef EVENTSYSTEM_EXITSYSTEM_HPP
#define EVENTSYSTEM_EXITSYSTEM_HPP

#include "EventSystem/BaseEventSystem.hpp"
#include "EventSystem/MapSystem.hpp"
#include <memory>
namespace EventSystem {
class ExitSystem : public BaseEventSystem {
public:
    ExitSystem(GameCore::MainGame &mainGame,
               const std::shared_ptr<MapSystem> map)
        : BaseEventSystem(mainGame),
          m_Map(map) {}
    void EventStart() override {
    };
    void EventUpdate() override {
        m_Map->ToNextMap();
        m_MainGame.EndEvent();
    };
    void EventEnd() override {};

private:
    std::shared_ptr<MapSystem> m_Map;
};
} // namespace EventSystem

#endif
