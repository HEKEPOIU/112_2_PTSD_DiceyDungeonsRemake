#ifndef EVENTSYSTEM_MAPS_MAP_HPP
#define EVENTSYSTEM_MAPS_MAP_HPP

#include "EventSystem/Maps/Node.hpp"
#include "EventSystem/Maps/NodeItem.hpp"
#include "GameCore/MainGame.hpp"
#include "Util/GameObject.hpp"
#include <array>
#include <glm/fwd.hpp>
#include <memory>
#include <unordered_map>
#include <vector>
namespace EventSystem::Maps {
// This enable_shared_from_this must inherit publicly.
// And Now I Learnd how to not pass std::makeShare<>(this) and raw &.
// But I am too late notice that.
class Map : public Util::GameObject, public std::enable_shared_from_this<Map> {
public:
    Map(GameCore::MainGame &game);
    void Start();
    void GetNextMap();
    std::vector<std::shared_ptr<Node>> GenerateEmptyMap();
    void RandomPlaceItem(std::vector<std::shared_ptr<Node>> &nodes);
    void SpawnPlayer();
    void SetPlayerPosition(glm::vec2 newPos);
    void ConnectMap(int playerSpotIndex,
                    std::vector<std::shared_ptr<Node>> &nodes);

    glm::ivec2 GetLinePosByIndex(int index);
    int GetIndexByLinePos(glm::ivec2 linePos);
    bool ConnectNodeNear(int indexA, int indexB);
    void ConnectNode(int indexA, int indexB);
    
private:
    GameCore::MainGame &m_Game;
    std::vector<std::shared_ptr<Node>> m_Nodes{};
    std::vector<std::shared_ptr<Util::GameObject>> m_Lines;
    static std::array<std::unordered_map<ItemType, int>, 5> m_ItemNum;
    std::shared_ptr<Util::GameObject> m_PlayerDice{};
    int m_CurrentLevel = -1;
    int m_MapX = 0;
    int m_MapY = 0;
};
} // namespace EventSystem::Maps
#endif
