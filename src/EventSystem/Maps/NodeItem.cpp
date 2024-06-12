#include "EventSystem/Maps/NodeItem.hpp"
#include "Character/Enemys/EnemyFactory.hpp"
#include "EventSystem/BattleSystem.hpp"
#include "EventSystem/ExitSystem.hpp"
#include "GameCore/MainGame.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include <memory>

namespace EventSystem::Maps {

NodeItem::NodeItem(GameCore::MainGame &game,const std::shared_ptr<Map> &map, ItemType itemType)
    : m_Owner(map),
      m_Game(game) {
    InitEventByType(itemType);
    SetZIndex(5);
};

void NodeItem::InitEventByType(ItemType type) {
    switch (type) {
    case ItemType::ENEMY: {
        auto enemy = Character::Enemys::EnemyFactory::GetRandomEnemy({1});
        m_Event = std::make_shared<BattleSystem>(m_Game, enemy);
        SetDrawable(enemy->GetLevelDrawable());
        m_Offset = {-30, 85};
        m_Transform.scale = {.65f, .65f};
        break;
    }
    case ItemType::APPLE: {
        LOG_ERROR("APPLE is Not Impl");
        break;
    }
    case ItemType::BOX: {
        LOG_ERROR("BOX is Not Impl");
        break;
    }
    case ItemType::CHANGESTORE: {
        LOG_ERROR("CHANGESTORE is Not Impl");
        break;
    }
    case ItemType::FORGE: {
        LOG_ERROR("FORGE is Not Impl");
        break;
    }
    case ItemType::GOLDSTORE: {
        LOG_ERROR("GOLDSTORE is Not Impl");
        break;
    }
    case ItemType::EXIT: {
        m_Event = std::make_shared<ExitSystem>(m_Game, m_Owner);
        SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Exit.png"));  
        m_Offset = {0,30};
        m_Transform.scale = {.9,.9};
        break;
    } break;
    }
}
} // namespace EventSystem::Maps
