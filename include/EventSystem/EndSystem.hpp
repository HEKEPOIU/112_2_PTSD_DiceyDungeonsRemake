#ifndef EVENTSYSTEM_ENDSYSTEM_HPP
#define EVENTSYSTEM_ENDSYSTEM_HPP

#include "EventSystem/BaseEventSystem.hpp"

namespace EventSystem {
class EndSystem : public BaseEventSystem {

public:
    EndSystem(GameCore::MainGame &mainGame);
    void EventStart() override;
    void EventUpdate() override;
    void EventEnd() override;

private:
    std::shared_ptr<Util::GameObject> m_TitleBtn;
    std::shared_ptr<Util::GameObject> m_EndGameBtn;
    std::shared_ptr<Util::GameObject> m_Character;
    std::shared_ptr<Util::GameObject> m_WinIcon;
};
} // namespace EventSystem
#endif
