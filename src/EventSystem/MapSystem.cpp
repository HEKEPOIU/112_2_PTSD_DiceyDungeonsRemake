#include "EventSystem/MapSystem.hpp"
#include "EventSystem/Maps/Map.hpp"
#include "Util/Image.hpp"
#include <memory>

namespace EventSystem {
MapSystem::MapSystem(GameCore::MainGame &mainGame)
    : BaseEventSystem(mainGame) {
    SetDrawable(std::make_shared<Util::Image>(
        RESOURCE_DIR "/graphics/backgrounds/overworld/ice/static_1080.png"));
    m_Current = std::make_shared<Maps::Map>(mainGame); 
    AddChild(m_Current);
}

void MapSystem::EventStart() {
    m_Current->GetNextMap();
    m_Current->SpawnPlayer();
}

void MapSystem::EventUpdate() {}

void MapSystem::EventEnd() {}

} // namespace EventSystem
