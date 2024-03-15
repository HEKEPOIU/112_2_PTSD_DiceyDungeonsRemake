#ifndef EVENTSYSTEM_BASEEVENTSYSTEM_HPP
#define EVENTSYSTEM_BASEEVENTSYSTEM_HPP

#include "Util/GameObject.hpp"
#include <memory>
namespace GameCore {
class MainGame;
} // namespace GameCore
namespace EventSystem {
class BaseEventSystem : public Util::GameObject {
public:
    BaseEventSystem(std::shared_ptr<GameCore::MainGame> mainGame);
    virtual void EventStart() = 0;
    virtual void EventUpdate() = 0;
    virtual void EventEnd() = 0;

protected:
    std::shared_ptr<GameCore::MainGame> m_MainGame;
};

} // namespace EventSystem

#endif
