#ifndef EVENTSYSTEM_ENDSYSTEM_HPP
#define EVENTSYSTEM_ENDSYSTEM_HPP

#include "EventSystem/BaseEventSystem.hpp"
#include <string>

namespace EventSystem {
enum class EndState { WIN, Fail };
class EndSystem : public BaseEventSystem {

public:
    EndSystem(GameCore::MainGame &mainGame, EndState state);
    void EventStart() override;
    void EventUpdate() override;
    void EventEnd() override;

private:
    std::shared_ptr<Util::GameObject> m_TitleBtn;
    std::shared_ptr<Util::GameObject> m_EndGameBtn;
    std::shared_ptr<Util::GameObject> m_Character;
    std::shared_ptr<Util::GameObject> m_WinIcon;
    const std::string m_EndText;
};
} // namespace EventSystem
#endif
