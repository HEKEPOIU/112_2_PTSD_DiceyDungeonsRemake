#include "EventSystem/Maps/Node.hpp"
#include "EventSystem/Maps/NodeItem.hpp"
#include "GameCore/MainGame.hpp"
#include "Util/Image.hpp"
#include <cwchar>
#include <glm/fwd.hpp>
#include <iostream>
#include <memory>
#include <random>

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
    if (m_Item == nullptr)
        return nullptr;
    return m_Item;
}
void Node::SetItem(const std::shared_ptr<Maps::NodeItem> &item) {
    if (m_Item != nullptr) {
        std::cout << "Remove" << std::endl;
        RemoveChild(m_Item);
    }
    m_Item = item;
    m_Item->m_Transform.translation =
        m_Transform.translation + m_Item->GetPositionOffset();
    AddChild(m_Item);
}

bool Node::IsConnected(std::shared_ptr<Node> node) {
    return std::find(m_Connect.begin(), m_Connect.end(), node) !=
           m_Connect.end();
}

void Node::AddConnection(const std::shared_ptr<Node> &node) {
    m_Connect.push_back(node);
}

bool Node::IsIsolated() {
    return m_Connect.empty();
}

void Node::RemoveItem() {
    m_Item = nullptr;
}

std::shared_ptr<Node>
Node::GetTopRight(std::vector<std::shared_ptr<Node>> path) {
    for (auto node : m_Connect) {
        glm::vec2 dir = node->m_Transform.translation - m_Transform.translation;
        glm::vec2 normalizeDir =
            glm::clamp(dir, glm::vec2(-1.0f), glm::vec2(1.0f));
        auto it = std::find(path.begin(), path.end(), node);
        if (it != path.end()) continue;
            if (normalizeDir == glm::vec2{1, 1}) {
                return node;
            }
    }
    return nullptr;
}
std::shared_ptr<Node>
Node::GetBottomRight(std::vector<std::shared_ptr<Node>> path) {
    for (auto node : m_Connect) {
        glm::vec2 dir = node->m_Transform.translation - m_Transform.translation;
        glm::vec2 normalizeDir =
            glm::clamp(dir, glm::vec2(-1.0f), glm::vec2(1.0f));
        auto it = std::find(path.begin(), path.end(), node);
        if (it != path.end()) continue;
            if (normalizeDir == glm::vec2{1, -1}) {
                return node;
            }
    }
    return nullptr;
}
std::shared_ptr<Node>
Node::GetTopLeft(std::vector<std::shared_ptr<Node>> path) {
    for (auto node : m_Connect) {
        glm::vec2 dir = node->m_Transform.translation - m_Transform.translation;
        glm::vec2 normalizeDir =
            glm::clamp(dir, glm::vec2(-1.0f), glm::vec2(1.0f));
        auto it = std::find(path.begin(), path.end(), node);
        if (it != path.end()) continue;
            if (normalizeDir == glm::vec2{-1, 1}) {
                return node;
            }
    }
    return nullptr;
}
std::shared_ptr<Node>
Node::GetBottomLeft(std::vector<std::shared_ptr<Node>> path) {
    for (auto node : m_Connect) {
        glm::vec2 dir = node->m_Transform.translation - m_Transform.translation;
        glm::vec2 normalizeDir =
            glm::clamp(dir, glm::vec2(-1.0f), glm::vec2(1.0f));
        auto it = std::find(path.begin(), path.end(), node);
        if (it != path.end()) continue;
            if (normalizeDir == glm::vec2{-1, -1}) {
                return node;
            }
    }
    return nullptr;
}

std::shared_ptr<Node>
Node::GetRandomLeft(std::vector<std::shared_ptr<Node>> path) {
    for (auto node : m_Connect) {
        glm::vec2 dir = node->m_Transform.translation - m_Transform.translation;
        glm::vec2 normalizeDir =
            glm::clamp(dir, glm::vec2(-1.0f), glm::vec2(1.0f));
        auto it = std::find(path.begin(), path.end(), node);
        if (it != path.end()) continue;
            if (normalizeDir.x == -1) {
                return node;
            }
    }
    return nullptr;
}

std::shared_ptr<Node>
Node::GetRandomRight(std::vector<std::shared_ptr<Node>> path) {
    for (auto node : m_Connect) {
        glm::vec2 dir = node->m_Transform.translation - m_Transform.translation;
        glm::vec2 normalizeDir =
            glm::clamp(dir, glm::vec2(-1.0f), glm::vec2(1.0f));
        auto it = std::find(path.begin(), path.end(), node);
        if (it != path.end()) continue;
            if (normalizeDir.x == 1) {
                return node;
            }
    }
    return nullptr;
}

std::shared_ptr<Node>
Node::GetRandomTop(std::vector<std::shared_ptr<Node>> path) {
    for (auto node : m_Connect) {
        glm::vec2 dir = node->m_Transform.translation - m_Transform.translation;
        glm::vec2 normalizeDir =
            glm::clamp(dir, glm::vec2(-1.0f), glm::vec2(1.0f));
        auto it = std::find(path.begin(), path.end(), node);
        if (it != path.end()) continue;
            if (normalizeDir.y == 1) {
                return node;
            }
    }
    return nullptr;
}

std::shared_ptr<Node>
Node::GetRandomBottom(std::vector<std::shared_ptr<Node>> path) {
    for (auto node : m_Connect) {
        glm::vec2 dir = node->m_Transform.translation - m_Transform.translation;
        glm::vec2 normalizeDir =
            glm::clamp(dir, glm::vec2(-1.0f), glm::vec2(1.0f));
        auto it = std::find(path.begin(), path.end(), node);
        if (it != path.end()) continue;
            if (normalizeDir.y == -1) {
                return node;
            }
    }
    return nullptr;
}

std::shared_ptr<Node> Node::GetRandom(std::vector<std::shared_ptr<Node>> path) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned short> disY(0, m_Connect.size() - 1);
    return m_Connect[disY(gen)];
}
} // namespace EventSystem::Maps
