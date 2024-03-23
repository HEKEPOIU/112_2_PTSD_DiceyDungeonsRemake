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
      m_CurrentBattle(currentBattle),
      m_Slider(std::make_shared<Utils::Slider>(
          RESOURCE_DIR "/graphics/pack1.png",
          RESOURCE_DIR "/graphics/pack1.png",
          currentBattle.GetPlayer().first->GetCurrentHealth(), 0,
          currentBattle.GetPlayer().first->GetMaxHealth())) {
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

    SetPlayerUIInform();
}
BattleUIManager::~BattleUIManager() {
    m_CurrentBattle.GetPlayer().first->UnBindOnCurrentHealthChange(
        "PlayerHealthChanged");
    m_CurrentBattle.GetPlayer().first->UnBindOnMaxHealthChange(
        "PlayerMaxHealthChanged");
}

void BattleUIManager::OnCurrentHealthChange(int oldHealth, int newHealth) {
    LOG_ERROR("CurrentHealthChanged from {} to {}", oldHealth, newHealth);
}

void BattleUIManager::OnMaxHealthChange(int oldHealth, int newHealth) {
    LOG_ERROR("MaxHealthChanged from {} to {}", oldHealth, newHealth);
}

void BattleUIManager::SetPlayerUIInform() {

    glm::vec2 sliderSize = {.5, .5};
    glm::vec2 sliderPostion = {-475, -350};

    m_Slider->m_Transform.scale = sliderSize;
    m_Slider->GetChildren()[0]->m_Transform.scale = sliderSize;
    m_Slider->m_Transform.translation = sliderPostion;
    m_Slider->GetChildren()[0]->m_Transform.translation = sliderPostion;
    m_Slider->GetBaseImageSpriteSheet()->SetDrawRect({515, 80, 605, 90});
    m_Slider->GetChildren()[0]->m_Transform.rotation = glm::radians(90.f);
    m_Slider->GetFillImageSpriteSheet()->SetDrawRect({205, 925, 85, 605});

    // Player name displayer
    auto playerNameObj = std::make_shared<Util::GameObject>();
    playerNameObj->m_Transform.translation = {sliderPostion.x - 100,
                                              sliderPostion.y + 50};
    m_PlayerName = std::make_shared<Util::Text>(
        RESOURCE_DIR "/NotoSans-Regular.ttf", 35,
        m_CurrentBattle.GetPlayer().first->GetName(),
        Util::Color(255, 255, 255));
    playerNameObj->SetDrawable(m_PlayerName);
    playerNameObj->SetZIndex(1);

    AddChild(m_Slider);
    AddChild(playerNameObj);
}
} // namespace UI
