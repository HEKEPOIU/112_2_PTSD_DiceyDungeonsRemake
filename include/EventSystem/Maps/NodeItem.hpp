#ifndef EVENTSYSTEM_MAPS_ITEM_HPP
#define EVENTSYSTEM_MAPS_ITEM_HPP

#include "EventSystem/BaseEventSystem.hpp"
#include "GameCore/MainGame.hpp"
#include "Util/GameObject.hpp"
#include <glm/fwd.hpp>
#include <memory>

namespace EventSystem::Maps {
class Map;
}

namespace EventSystem::Maps {
enum class ItemType {
    ENEMY,
    APPLE,
    BOX,
    GOLDSTORE,
    CHANGESTORE,
    FORGE,
    EXIT,
};
class NodeItem : public Util::GameObject {
public:
    NodeItem(GameCore::MainGame &game, const std::shared_ptr<Map> &map,
             ItemType itemType);
    std::shared_ptr<BaseEventSystem> GetItem() {
        if (isVisited)
            return nullptr;
        isVisited = true;
        return m_Event;
    };
    void InitEventByType(ItemType type);
    glm::vec2 GetPositionOffset() const { return m_Offset; }

protected:
    std::shared_ptr<BaseEventSystem> m_Event;
    std::shared_ptr<Map> m_Owner;
    glm::vec2 m_Offset = {0, 0};
    GameCore::MainGame &m_Game;
    bool isVisited = false;
};
} // namespace EventSystem::Maps
#endif
