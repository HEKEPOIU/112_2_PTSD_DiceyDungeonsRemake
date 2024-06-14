#ifndef EVENTSYSTEM_APPLESYSTEM_HPP
#define EVENTSYSTEM_APPLESYSTEM_HPP

#include "EventSystem/BaseEventSystem.hpp"
#include "GameCore/MainGame.hpp"

namespace EventSystem {
class AppleSystem : public BaseEventSystem {
public:
    AppleSystem(GameCore::MainGame &mainGame)
        : BaseEventSystem(mainGame) {}
    void EventStart() override {
        m_MainGame.GetPlayerDice()->ModifyCurrentHealth(5);
    };
    void EventUpdate() override {
        m_MainGame.EndEvent();
    };
    void EventEnd() override {};
};
} // namespace EventSystem
#endif
