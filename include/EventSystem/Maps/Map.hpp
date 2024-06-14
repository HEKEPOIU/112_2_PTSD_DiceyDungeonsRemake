#ifndef EVENTSYSTEM_MAPS_MAP_HPP
#define EVENTSYSTEM_MAPS_MAP_HPP

#include "EventSystem/BaseEventSystem.hpp"
#include "EventSystem/Maps/Node.hpp"
#include "EventSystem/Maps/NodeItem.hpp"
#include "GameCore/MainGame.hpp"
#include "Util/GameObject.hpp"
#include <array>
#include <glm/fwd.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

namespace EventSystem {
class MapSystem;
}

namespace EventSystem::Maps {
// This enable_shared_from_this must inherit publicly.
// And Now I Learnd how to not pass std::makeShare<>(this) and raw &.
// But I am too late notice that.
class Map : public Util::GameObject, public std::enable_shared_from_this<Map> {
public:
    Map(GameCore::MainGame &game, const std::shared_ptr<MapSystem>& owner);
    void Start();
    void GetNextMap();
    std::vector<std::shared_ptr<Node>> GenerateEmptyMap();
    void RandomPlaceItem(std::vector<std::shared_ptr<Node>> &nodes);
    void SpawnPlayer();
    void SetPlayerPosition(glm::vec2 newPos);
    std::shared_ptr<NodeItem> PlayersEndAt(std::shared_ptr<Node> &node);
    void ConnectMap(int playerSpotIndex,
                    std::vector<std::shared_ptr<Node>> &nodes);

    glm::ivec2 GetLinePosByIndex(int index);
    int GetIndexByLinePos(glm::ivec2 linePos);
    bool ConnectNodeNear(int indexA, int indexB);
    void ConnectNode(int indexA, int indexB);
    std::vector<std::shared_ptr<Node>> &GetNodes();
    std::shared_ptr<Node> GetPlayerNode();
    std::vector<std::shared_ptr<Node>> GetPath(std::shared_ptr<Node> &from,
                                               std::shared_ptr<Node> &to);
    std::shared_ptr<Node>
    GetTargetDirNode(std::shared_ptr<Node> &node, glm::vec2 dir,
                     std::vector<std::shared_ptr<Node>> path);
    std::shared_ptr<MapSystem> GetOwner();

private:
    GameCore::MainGame &m_Game;
    std::shared_ptr<MapSystem> m_Owner;
    std::vector<std::shared_ptr<Node>> m_Nodes{};
    std::vector<std::shared_ptr<Util::GameObject>> m_Lines;
    static std::array<std::unordered_map<ItemType, int>, 5> m_ItemNum;
    std::shared_ptr<Node> m_PlayerNode{};
    int m_CurrentLevel = -1;
    int m_MapX = 0;
    int m_MapY = 0;
    int m_PlayerPos = -1;
};
} // namespace EventSystem::Maps
#endif
