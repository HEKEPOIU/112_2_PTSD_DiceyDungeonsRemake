#ifndef EVENTSYSTEM_EXITSYSTEM_HPP
#define EVENTSYSTEM_EXITSYSTEM_HPP

#include "EventSystem/BaseEventSystem.hpp"
#include "EventSystem/Maps/Map.hpp"
#include "Util/Logger.hpp"
#include <memory>
namespace EventSystem {
class ExitSystem : public BaseEventSystem {
public:
    ExitSystem(GameCore::MainGame &mainGame, const std::shared_ptr<Maps::Map> map)
        : BaseEventSystem(mainGame), m_Map(map) {}
    void EventStart() override {
        m_Map->GetNextMap();
    };
    void EventUpdate() override {};
    void EventEnd() override {};
private:
    std::shared_ptr<Maps::Map> m_Map;
};
} // namespace EventSystem

#endif
