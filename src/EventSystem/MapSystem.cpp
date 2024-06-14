#include "EventSystem/MapSystem.hpp"
#include "EventSystem/BaseEventSystem.hpp"
#include "EventSystem/Maps/Map.hpp"
#include "Player/PlayerMapInput.hpp"
#include "Util/Image.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>
#include <thread>

namespace EventSystem {
MapSystem::MapSystem(GameCore::MainGame &mainGame)
    : BaseEventSystem(mainGame) {
    SetDrawable(std::make_shared<Util::Image>(
        RESOURCE_DIR "/graphics/backgrounds/overworld/ice/static_1080.png"));
}

void MapSystem::EventStart() {
    if (ToNextLevel) {
        if (m_Current == nullptr) {
            m_Current =
                std::make_shared<Maps::Map>(m_MainGame, shared_from_this());
            AddChild(m_Current);
        }
        m_Current->GetNextMap();
        m_Current->SpawnPlayer();
        ToNextLevel = false;
    }
    m_PlayerInput =
        std::make_shared<Player::PlayerMapInput>(shared_from_this());
    m_MoveTimer->SetOnTimerEnd([this]() { m_CanMove = true; });
}

void MapSystem::EventUpdate() {
    m_PlayerInput->InputUpdate();
    m_MoveTimer->Update();
    CheckEventEnd();
}

void MapSystem::EventEnd() {
    m_MoveTimer->RemoveOnTimerEnd();
}

std::vector<std::shared_ptr<Maps::Node>> &MapSystem::GetMapNodes() {
    return m_Current->GetNodes();
}
void MapSystem::MovePlayerToTarget(std::shared_ptr<Maps::Node> &target) {
    if (m_IsMoving)
        return;
    m_IsMoving = true;
    auto playerNode = m_Current->GetPlayerNode();
    auto pathToTarget = m_Current->GetPath(playerNode, target);
    std::thread moveThread([this, pathToTarget]() mutable {
        size_t i = 0;
        while (i < pathToTarget.size()) {
            m_Current->SetPlayerPosition(
                pathToTarget[i]->m_Transform.translation);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            i++;
        }
        m_IsMoving = false;
        if (pathToTarget.size() == 0) {
            return;
        }
        m_EventItem = m_Current->PlayersEndAt(pathToTarget.back());
    });
    moveThread.detach(); // 分离线程，主线程不会被阻塞
}

void MapSystem::CheckEventEnd() {
    if (m_EventItem != nullptr) {
        m_MainGame.AppendEvnet(m_EventItem->GetItem());
        m_MainGame.AppendEvnet(shared_from_this());
        m_MainGame.EndEvent();
        m_EventItem = nullptr;
    } else if (m_EventToStart != nullptr) {
        m_MainGame.AppendEvnet(m_EventToStart);
        m_MainGame.EndEvent();
    }
}
void MapSystem::ToNextEvent(const std::shared_ptr<BaseEventSystem> &event) {
    m_EventToStart = event;
}

void MapSystem::ToNextMap() {
    ToNextLevel = true;
}
} // namespace EventSystem
