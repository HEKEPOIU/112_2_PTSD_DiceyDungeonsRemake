#include "EventSystem/Maps/Map.hpp"
#include "EventSystem/EndSystem.hpp"
#include "EventSystem/MapSystem.hpp"
#include "EventSystem/Maps/NodeItem.hpp"
#include "GameCore/MainGame.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <cmath>
#include <cstddef>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <ostream>
#include <random>
#include <utility>
#include <vector>

namespace EventSystem::Maps {
Map::Map(GameCore::MainGame &game, const std::shared_ptr<MapSystem> &owner)
    : Util::GameObject(),
      m_Game(game),
      m_Owner(owner) {}

std::vector<std::shared_ptr<Node>> Map::GenerateEmptyMap() {

    int totalItemNum = 0;
    for (auto map : m_ItemNum[m_CurrentLevel]) {
        totalItemNum += map.second;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned short> disY(4, 6);
    std::uniform_int_distribution<unsigned short> disX(4, 7);
    m_MapX = 0;
    m_MapY = 0;
    do {
        m_MapX = disX(gen);
        m_MapY = disY(gen);
        std::cout << round((m_MapX * m_MapY) / 2.f) << std::endl;
    } while (round((m_MapX * m_MapY) / 2.f) < totalItemNum + 1);
    std::cout << "X" << m_MapX << "Y" << m_MapY << std::endl;
    glm::ivec2 nodeSize = {189, 122};
    int xSpecing = 30;
    int xLength = (m_MapX - 1) * nodeSize.x + (m_MapX - 1) * xSpecing;
    int yLength = (m_MapY - 1) * nodeSize.y;
    int startX = -(xLength / 2);
    int startY = 30 + (yLength / 2);
    std::vector<std::shared_ptr<Node>> nodeList;
    for (int x = 0; x < m_MapX; x += 1) {
        for (int y = 0; y < m_MapY; y += 2) {
            auto node = std::make_shared<Node>(m_Game);
            node->SetPositionWithChild({startX + (x * (nodeSize.x + xSpecing)),
                                        startY - (y * nodeSize.y)});
            nodeList.push_back(node);
        }
        x++;
        if (x >= m_MapX) {
            break;
        }
        for (int y = 1; y < m_MapY; y += 2) {
            auto node = std::make_shared<Node>(m_Game);
            node->SetPositionWithChild({startX + (x * (nodeSize.x + xSpecing)),
                                        startY - (y * nodeSize.y)});
            nodeList.push_back(node);
        }
    }
    return nodeList;
};

void Map::RandomPlaceItem(std::vector<std::shared_ptr<Node>> &nodes) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned short> disX(0, nodes.size() - 1);
    for (auto pair : m_ItemNum[m_CurrentLevel]) {
        for (int i = 0; i < pair.second; i++) {
            while (true) {
                int index = disX(gen);
                if (nodes[index]->GetItem() == nullptr) {
                    nodes[index]->SetItem(std::make_shared<NodeItem>(
                        m_Game, shared_from_this(), pair.first));
                    break;
                }
            }
        }
    }
}

void Map::GetNextMap() {
    for (auto node : m_Nodes) {
        RemoveChild(node);
    }
    for (auto line : m_Lines) {
        RemoveChild(line);
    }
    m_Nodes.clear();
    m_Lines.clear();
    m_CurrentLevel += 1;
    if (m_CurrentLevel > m_ItemNum.size() - 1) {
        m_Owner->ToNextEvent(std::make_shared<EndSystem>(m_Game, EndState::WIN));
        return;
    }
    m_Nodes = GenerateEmptyMap();
    RandomPlaceItem(m_Nodes);
    for (auto item : m_Nodes) {
        AddChild(item);
    }
}

void Map::SpawnPlayer() {
    if (m_CurrentLevel > m_ItemNum.size() - 1) {
        return;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned short> disX(0, m_Nodes.size() - 1);
    int playerIndex;
    while (true) {
        playerIndex = disX(gen);
        std::cout << "Try To Place Item" << std::endl;
        if (m_Nodes[playerIndex]->GetItem() == nullptr) {
            m_Nodes[playerIndex]->SetItem(std::make_shared<NodeItem>(
                m_Game, shared_from_this(), ItemType::PLAYER));
            m_PlayerNode = m_Nodes[playerIndex];
            break;
        }
    }
    ConnectMap(playerIndex, m_Nodes);
}

void Map::ConnectMap(int playerSpotIndex,
                     std::vector<std::shared_ptr<Node>> &nodes) {
    std::map<int, std::shared_ptr<Node>> haveItemNodes;
    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i]->GetItem() != nullptr) {
            haveItemNodes.insert(
                std::pair<int, std::shared_ptr<Node>>(i, nodes[i]));
        }
    }
    for (auto it = haveItemNodes.rbegin(); it != haveItemNodes.rend(); ++it) {
        ConnectNode(playerSpotIndex, it->first);
    }
    for (auto node : m_Nodes) {
        if (node->IsIsolated()) {
            RemoveChild(node);
        }
    }
    m_Nodes.erase(std::remove_if(m_Nodes.begin(), m_Nodes.end(),
                                 [](const std::shared_ptr<Node> &node) {
                                     return node->IsIsolated();
                                 }),
                  m_Nodes.end());
}

glm::ivec2 Map::GetLinePosByIndex(int index) {
    int part = index / m_MapY + 1;
    int line =
        ((index + (m_MapY / 2)) / m_MapY) == part ? 2 * part - 1 : 2 * part - 2;
    bool isOdd = (line % 2 == 0) ? false : true;
    int preLineNum = 0;
    if (m_MapY % 2 == 0) {
        preLineNum = m_MapY / 2;
    } else {
        preLineNum = isOdd ? m_MapY / 2 + 1 : m_MapY / 2;
    }
    int lineIndex = (index) % m_MapY;
    lineIndex = isOdd ? lineIndex - preLineNum : lineIndex;
    return {line, lineIndex};
};

int Map::GetIndexByLinePos(glm::ivec2 linePos) {
    int line = linePos.x;
    int lineIndex = linePos.y;
    int index = 0;
    for (int i = 1; i < line + 1; i++) {
        bool isOdd = (i % 2 == 0) ? false : true;
        int preLineNum = 0;
        if (m_MapY % 2 == 0) {
            preLineNum = m_MapY / 2;
        } else {
            preLineNum = isOdd ? m_MapY / 2 + 1 : m_MapY / 2;
        }
        index += preLineNum;
    }
    index += lineIndex;

    return index;
}

void Map::ConnectNode(int indexA, int indexB) {
    std::cout << "Connect: " << indexA << " To: " << indexB << std::endl;
    glm::ivec2 lineDataA = GetLinePosByIndex(indexA);
    glm::vec2 pA = m_Nodes[indexA]->m_Transform.translation;
    glm::vec2 pB = m_Nodes[indexB]->m_Transform.translation;
    glm::vec2 nodeDir = pB - pA;

    if (nodeDir.y == 0 && nodeDir.x == 0) {
        return;
    }

    glm::vec2 dir = glm::clamp(nodeDir, glm::vec2(-1.0f), glm::vec2(1.0f));
    if (dir.x > 0) {
        lineDataA.x += 1;
    } else if (dir.x < 0) {
        lineDataA.x -= 1;
    } else {
        if (lineDataA.x >= m_MapX - 1) {
            lineDataA.x -= 1;
        } else if (lineDataA.x <= 0) {
            lineDataA.x += 1;
        } else {
            int num = 0;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> disX(-1, 1);
            while (num == 0) {
                num = disX(gen);
            }
            lineDataA.x += num;
        }
    }

    bool isOdd = (lineDataA.x % 2 == 0) ? false : true;
    int lineNum = 0;
    if (m_MapY % 2 == 0) {
        lineNum = m_MapY / 2;
    } else {
        lineNum = isOdd ? m_MapY / 2 + 1 : m_MapY / 2;
    }

    if (dir.y > 0) {
        if (isOdd) {
            lineDataA.y -= 1;
        } else {
        }
    } else if (dir.y < 0) {
        if (isOdd) {

        } else {
            lineDataA.y += 1;
        }
    } else {
        if (lineDataA.y >= lineNum - 1) {
            if (isOdd) {
                lineDataA.y -= 1;
            } else {
            }
        } else if (lineDataA.y <= 0) {
            if (isOdd) {
            } else {
            }
        } else {
            int num = 0;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> disX(-1, 0);
            lineDataA.y += num;
        }
    }
    bool isWork = ConnectNodeNear(indexA, GetIndexByLinePos(lineDataA));
    ConnectNode(GetIndexByLinePos(lineDataA), indexB);
}

std::vector<std::shared_ptr<Node>> Map::GetPath(std::shared_ptr<Node> &from,
                                                std::shared_ptr<Node> &to) {
    std::shared_ptr<Node> cache = from;
    std::vector<std::shared_ptr<Node>> path;
    glm::vec2 targetPos = to->m_Transform.translation;
    while (true) {
        glm::vec2 pA = cache->m_Transform.translation;
        glm::vec2 dir = targetPos - pA;
        glm::vec2 normalizeDir =
            glm::clamp(dir, glm::vec2(-1.0f), glm::vec2(1.0f));
        std::shared_ptr<Node> next =
            GetTargetDirNode(cache, normalizeDir, path);
        if (next == nullptr) {
            break;
        }
        path.push_back(next);
        cache = next;
    }
    return path;
}
void Map::SetPlayerPosition(glm::vec2 newPos) {
    auto playerItem = m_PlayerNode->GetItem();
    playerItem->m_Transform.translation = newPos;
}

std::shared_ptr<Node> Map::GetPlayerNode() {
    return m_PlayerNode;
}

std::shared_ptr<NodeItem> Map::PlayersEndAt(std::shared_ptr<Node> &node) {
    auto nodeItem = node->GetItem();
    node->SetItem(m_PlayerNode->GetItem());
    m_PlayerNode->RemoveItem();
    m_PlayerNode = node;
    return nodeItem;
}

std::shared_ptr<Node>
Map::GetTargetDirNode(std::shared_ptr<Node> &node, glm::vec2 dir,
                      std::vector<std::shared_ptr<Node>> path) {
    std::shared_ptr<Node> target = nullptr;
    if (target == nullptr && dir == glm::vec2{1, 1}) {
        target = node->GetTopRight(path);
    } else if (target == nullptr && dir == glm::vec2{1, -1}) {
        target = node->GetBottomRight(path);
    } else if (target == nullptr && dir == glm::vec2{-1, 1}) {
        target = node->GetTopLeft(path);
    } else if (target == nullptr && dir == glm::vec2{-1, -1}) {
        target = node->GetBottomLeft(path);
    }
    if (target == nullptr && dir.y == 1) {
        target = node->GetRandomTop(path);
    }
    if (target == nullptr && dir.y == -1) {
        target = node->GetRandomBottom(path);
    }
    if (target == nullptr && dir.x == 1) {
        target = node->GetRandomRight(path);
    }
    if (target == nullptr && dir.x == -1) {
        target = node->GetRandomLeft(path);
    }
    if (dir == glm::vec2{0, 0}) {
        return nullptr;
    }
    if (target == nullptr) {
        target = node->GetRandom(path);
    }
    return target;
}

bool Map::ConnectNodeNear(int indexA, int indexB) {
    if (m_Nodes[indexA]->IsConnected(m_Nodes[indexB])) {
        std::cout << "Already connect" << std::endl;
        return false;
    }
    glm::vec2 pA = m_Nodes[indexA]->m_Transform.translation;
    glm::vec2 pB = m_Nodes[indexB]->m_Transform.translation;
    glm::vec2 center = {(pA.x + pB.x) / 2, (pA.y + pB.y) / 2};
    m_Nodes[indexA]->AddConnection(m_Nodes[indexB]);
    m_Nodes[indexB]->AddConnection(m_Nodes[indexA]);
    auto line = std::make_shared<Util::GameObject>();
    line->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Line.png"));
    glm::vec2 dir = pA - pB;
    line->m_Transform.translation = center;
    line->m_Transform.scale = {3.5, 3.5};
    line->m_Transform.rotation = -atan2(dir.x, dir.y);
    line->SetZIndex(3);
    m_Lines.push_back(line);
    AddChild(line);
    return true;
}

std::vector<std::shared_ptr<Node>> &Map::GetNodes() {
    return m_Nodes;
}

std::shared_ptr<MapSystem> Map::GetOwner() {
    return m_Owner;
}

std::array<std::unordered_map<ItemType, int>, 5> Map::m_ItemNum = {
    std::unordered_map<ItemType, int>{
        {ItemType::ENEMY, 2}, {ItemType::BOX, 1}, {ItemType::EXIT, 1}},
    std::unordered_map<ItemType, int>{{ItemType::ENEMY, 3},
                                      {ItemType::BOX, 1},
                                      {ItemType::APPLE, 1},
                                      {ItemType::GOLDSTORE, 1},
                                      {ItemType::EXIT, 1}},
    std::unordered_map<ItemType, int>{{ItemType::ENEMY, 3},
                                      {ItemType::BOX, 1},
                                      {ItemType::APPLE, 2},
                                      {ItemType::GOLDSTORE, 1},
                                      {ItemType::FORGE, 1},
                                      {ItemType::EXIT, 1}},
    std::unordered_map<ItemType, int>{{ItemType::ENEMY, 3},
                                      {ItemType::BOX, 1},
                                      {ItemType::APPLE, 1},
                                      {ItemType::CHANGESTORE, 1},
                                      {ItemType::EXIT, 1}},
    std::unordered_map<ItemType, int>{{ItemType::ENEMY, 4},
                                      {ItemType::BOX, 1},
                                      {ItemType::APPLE, 2},
                                      {ItemType::GOLDSTORE, 1},
                                      {ItemType::FORGE, 1},
                                      {ItemType::EXIT, 1}},

};
} // namespace EventSystem::Maps
