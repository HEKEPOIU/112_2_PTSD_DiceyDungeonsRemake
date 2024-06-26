#ifndef EVENTSYSTEM_EMPTYSYSTEM_HPP
#define EVENTSYSTEM_EMPTYSYSTEM_HPP

#include "EventSystem/BaseEventSystem.hpp"
#include "Util/Logger.hpp"
#include "GameCore/MainGame.hpp"
namespace EventSystem {
class EmptySystem : public BaseEventSystem {
public:
    EmptySystem(GameCore::MainGame &mainGame)
        : BaseEventSystem(mainGame) {}
    void EventStart() override {
        LOG_ERROR("This system is empty, for test only");
    };
    void EventUpdate() override {
        m_MainGame.EndEvent();
    };
    void EventEnd() override {};
};
} // namespace EventSystem

#endif
