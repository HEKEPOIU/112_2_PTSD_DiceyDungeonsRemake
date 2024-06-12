#include "EventSystem/Maps/Node.hpp"
#include "EventSystem/Maps/NodeItem.hpp"
#include "GameCore/MainGame.hpp"
#include "Util/Image.hpp"
#include <cwchar>
#include <iostream>
#include <memory>

namespace EventSystem::Maps {

Node::Node(GameCore::MainGame &game,
           const std::shared_ptr<Maps::NodeItem> &item)
    : Util::GameObject(),
      m_Item(item),
      m_Game(game) {
    SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Node.png"));
    if (m_Item) {
        AddChild(m_Item);
    }
    SetZIndex(4);
}

const std::vector<std::shared_ptr<Node>> &Node::GetConnect() const {
    return m_Connect;
}

std::shared_ptr<Maps::NodeItem> Node::GetItem() {
    if(m_Item == nullptr) return nullptr;
    return m_Item;
}
void Node::SetItem(const std::shared_ptr<Maps::NodeItem> &item) {
    if(m_Item != nullptr){
        std::cout << "Remove" << std::endl;
        RemoveChild(m_Item);
    }
    m_Item = item;
    m_Item->m_Transform.translation = m_Transform.translation + m_Item->GetPositionOffset();
    AddChild(m_Item);
}

bool Node::IsConnected(std::shared_ptr<Node> node){
    return std::find(m_Connect.begin(), m_Connect.end(), node) != m_Connect.end();
}

void Node::AddConnection(const std::shared_ptr<Node>& node){
    m_Connect.push_back(node);
}
} // namespace EventSystem::Maps
