#include "UI/BattleUIManager.hpp"
#include "EventSystem/BattleSystem.hpp"
#include "UI/Utils/Slider.hpp"
#include "Util/Color.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include <functional>
#include <glm/fwd.hpp>
#include <memory>

namespace UI {
BattleUIManager::BattleUIManager(EventSystem::BattleSystem &currentBattle)
    : Util::GameObject(),
      m_CurrentBattle(currentBattle) {
    // TODO: This should be dependency injected base on context.
    SetDrawable(std::make_shared<Util::Image>(
        RESOURCE_DIR "/graphics/backgrounds/combat/castle/static_1080.png"));
    auto currentHpBoundFunction =
        std::bind(&BattleUIManager::OnCurrentHealthChange, this,
                  std::placeholders::_1, std::placeholders::_2);
    auto maxHpBoundFunction =
        std::bind(&BattleUIManager::OnMaxHealthChange, this,
                  std::placeholders::_1, std::placeholders::_2);

    m_CurrentBattle.GetPlayer().first->BindOnCurrentHealthChange(
        "PlayerHealthChanged", currentHpBoundFunction);
    m_CurrentBattle.GetPlayer().first->BindOnMaxHealthChange(
        "PlayerMaxHealthChanged", maxHpBoundFunction);

    LOG_ERROR("zindex of background is {}", GetZIndex());
    SetZIndex(-1);
    m_PlayerHpBar = std::make_shared<Utils::Slider>(
        RESOURCE_DIR "/graphics/pack1.png", RESOURCE_DIR "/graphics/pack1.png",
        currentBattle.GetPlayer().first->GetCurrentHealth(), 0,
        currentBattle.GetPlayer().first->GetMaxHealth(), GetZIndex() + 1);
    m_EnemyHpBar = std::make_shared<Utils::Slider>(
        RESOURCE_DIR "/graphics/pack1.png", RESOURCE_DIR "/graphics/pack1.png",
        currentBattle.GetEnemy().first->GetCurrentHealth(), 0,
        currentBattle.GetEnemy().first->GetMaxHealth(), GetZIndex() + 1);

    SetBattleBarInform(m_PlayerHpBar,
                       currentBattle.GetPlayer().first->GetName(), {-475, -350},
                       {.5, .5});
    SetBattleBarInform(m_EnemyHpBar, currentBattle.GetEnemy().first->GetName(),
                       {475, 400}, {.5, .5});
}
BattleUIManager::~BattleUIManager() {
    m_CurrentBattle.GetPlayer().first->UnBindOnCurrentHealthChange(
        "PlayerHealthChanged");
    m_CurrentBattle.GetPlayer().first->UnBindOnMaxHealthChange(
        "PlayerMaxHealthChanged");
}

void BattleUIManager::OnCurrentHealthChange(int oldHealth, int newHealth) {
    LOG_ERROR("CurrentHealthChanged from {} to {}", oldHealth, newHealth);
    m_PlayerHpBar->SetCurrentValue(newHealth);
}

void BattleUIManager::OnMaxHealthChange(int oldHealth, int newHealth) {
    LOG_ERROR("MaxHealthChanged from {} to {}", oldHealth, newHealth);
    m_PlayerHpBar->SetMaxValue(newHealth);
}

void BattleUIManager::SetBattleBarInform(
    const std::shared_ptr<Utils::Slider> &bar, const std::string &name,
    const glm::vec2 &pos, const glm::vec2 &scale) {

    bar->SetPostion(pos);
    bar->SetScale(scale);
    bar->GetFillObject()->m_Transform.rotation = glm::radians(90.f);

    bar->SetBaseImageSpriteSheet({515, 80, 605, 90});
    bar->SetFillImageSpriteSheet({205, 925, 85, 605});

    // Player name displayer
    auto nameObj = std::make_shared<Util::GameObject>();
    nameObj->m_Transform.translation = {pos.x - 100, pos.y + 50};
    m_PlayerName =
        std::make_shared<Util::Text>(RESOURCE_DIR "/NotoSans-Regular.ttf", 35,
                                     name, Util::Color(255, 255, 255));
    nameObj->SetDrawable(m_PlayerName);
    nameObj->SetZIndex(1);

    AddChild(bar);
    AddChild(nameObj);
}

void BattleUIManager::Update() {}

} // namespace UI
