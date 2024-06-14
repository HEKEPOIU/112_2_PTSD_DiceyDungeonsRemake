#ifndef EVENTSYSTEM_MAPSYSTEM_HPP
#define EVENTSYSTEM_MAPSYSTEM_HPP

#include "DiceUtils/Timer.hpp"
#include "EventSystem/BaseEventSystem.hpp"
#include "EventSystem/Maps/Map.hpp"
#include "EventSystem/Maps/Node.hpp"
#include "EventSystem/Maps/NodeItem.hpp"
#include "GameCore/MainGame.hpp"
#include <memory>
#include <vector>
namespace Player {
class PlayerMapInput;
}
namespace EventSystem {
class MapSystem : public BaseEventSystem,
                  public std::enable_shared_from_this<MapSystem> {
public:
    MapSystem(GameCore::MainGame &mainGame);
    void EventStart() override;
    void EventUpdate() override;
    void EventEnd() override;
    void ToNextMap();
    void MovePlayerToTarget(std::shared_ptr<Maps::Node> &target);
    std::vector<std::shared_ptr<Maps::Node>> &GetMapNodes();
    void ToNextEvent(const std::shared_ptr<BaseEventSystem> &event);

private:
    void CheckEventEnd();

    std::shared_ptr<Maps::Map> m_Current;
    std::shared_ptr<Player::PlayerMapInput> m_PlayerInput;
    std::unique_ptr<DiceUtils::Timer> m_MoveTimer =
        std::make_unique<DiceUtils::Timer>(1);
    std::shared_ptr<Maps::NodeItem> m_EventItem = nullptr;
    std::shared_ptr<BaseEventSystem> m_EventToStart = nullptr;
    bool m_CanMove = true;
    bool m_IsMoving = false;
    bool ToNextLevel = true;
};
} // namespace EventSystem

#endif
