#ifndef EVENTSYSTEM_MAPS_NODE_HPP
#define EVENTSYSTEM_MAPS_NODE_HPP

#include "EventSystem/BaseEventSystem.hpp"
#include "EventSystem/Maps/NodeItem.hpp"
#include "GameCore/MainGame.hpp"
#include "Util/GameObject.hpp"
#include <memory>
#include <vector>
namespace EventSystem::Maps {

class Node : public Util::GameObject {

public:
    Node(GameCore::MainGame &game,
         const std::shared_ptr<Maps::NodeItem> &item = nullptr);
    const std::vector<std::shared_ptr<Node>> &GetConnect() const;

    // Return null if no item on it.
    std::shared_ptr<Maps::NodeItem> GetItem();
    void SetItem(const std::shared_ptr<Maps::NodeItem> &item);

    void RemoveItem();
    void AddConnection(const std::shared_ptr<Node> &node);
    bool IsConnected(std::shared_ptr<Node> node);
    bool IsIsolated();
    std::shared_ptr<Node> GetTopRight(std::vector<std::shared_ptr<Node>> path);
    std::shared_ptr<Node>
    GetBottomRight(std::vector<std::shared_ptr<Node>> path);
    std::shared_ptr<Node> GetTopLeft(std::vector<std::shared_ptr<Node>> path);
    std::shared_ptr<Node>
    GetBottomLeft(std::vector<std::shared_ptr<Node>> path);
    std::shared_ptr<Node> GetRandomTop(std::vector<std::shared_ptr<Node>> path);
    std::shared_ptr<Node>
    GetRandomBottom(std::vector<std::shared_ptr<Node>> path);
    std::shared_ptr<Node>
    GetRandomLeft(std::vector<std::shared_ptr<Node>> path);
    std::shared_ptr<Node>
    GetRandomRight(std::vector<std::shared_ptr<Node>> path);
    std::shared_ptr<Node> GetRandom(std::vector<std::shared_ptr<Node>> path);

private:
    std::shared_ptr<Maps::NodeItem> m_Item;
    std::vector<std::shared_ptr<Node>> m_Connect;
    GameCore::MainGame &m_Game;
    bool m_IsHaveItem = false;
};
} // namespace EventSystem::Maps

#endif
