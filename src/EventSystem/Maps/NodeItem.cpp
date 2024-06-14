#include "EventSystem/Maps/NodeItem.hpp"
#include "Character/Enemys/EnemyFactory.hpp"
#include "EventSystem/AppleSystem.hpp"
#include "EventSystem/BattleSystem.hpp"
#include "EventSystem/BoxEvent.hpp"
#include "EventSystem/EmptySystem.hpp"
#include "EventSystem/ExitSystem.hpp"
#include "GameCore/MainGame.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/SpriteSheet.hpp"
#include <memory>

namespace EventSystem::Maps {

NodeItem::NodeItem(GameCore::MainGame &game, const std::shared_ptr<Map> &map,
                   ItemType itemType)
    : Util::GameObject(),
      m_Owner(map),
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
        m_Event = std::make_shared<AppleSystem>(m_Game);
        auto drawable = std::make_shared<Util::SpriteSheet>(
            RESOURCE_DIR "/graphics/pack1.png");
        drawable->SetDrawRect({1778, 0, 269, 219});
        m_Transform.scale = {0.4f, 0.4f};
        m_Transform.rotation = glm::radians(90.f);
        m_Offset = {0, 30};
        SetDrawable(drawable);
        break;
    }
    case ItemType::BOX: {
        m_Event = std::make_shared<BoxEvent>(m_Game);
        auto drawable = std::make_shared<Util::SpriteSheet>(
            RESOURCE_DIR "/graphics/pack1.png");
        drawable->SetDrawRect({1675, 264, 186, 245});
        m_Transform.scale = {0.5f, 0.5f};
        m_Transform.rotation = glm::radians(90.f);
        m_Offset = {0, 30};
        SetDrawable(drawable);
        break;
    }
    case ItemType::CHANGESTORE: {
        LOG_ERROR("CHANGESTORE is Not Impl");
        m_Event = std::make_shared<EmptySystem>(m_Game);
        break;
    }
    case ItemType::FORGE: {
        LOG_ERROR("FORGE is Not Impl");
        m_Event = std::make_shared<EmptySystem>(m_Game);
        break;
    }
    case ItemType::GOLDSTORE: {
        LOG_ERROR("GOLDSTORE is Not Impl");
        m_Event = std::make_shared<EmptySystem>(m_Game);
        break;
    }
    case ItemType::EXIT: {
        m_Event = std::make_shared<ExitSystem>(m_Game, m_Owner->GetOwner());
        SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Exit.png"));
        m_Offset = {0, 30};
        m_Transform.scale = {.9, .9};
        break;
    } break;
    case ItemType::PLAYER:
        auto playerDiceimg = m_Game.GetPlayerDice()->GetLevelDrawable();
        SetDrawable(playerDiceimg);
        SetZIndex(10);
        m_Transform.scale = {1.5, 1.5};
        m_Offset = {0, 20};
        break;
    }
}
} // namespace EventSystem::Maps
