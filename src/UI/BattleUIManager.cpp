#include "UI/BattleUIManager.hpp"
#include "EventSystem/BattleSystem.hpp"
#include "UI/Utils/EffectBar.hpp"
#include "UI/Utils/Slider.hpp"
#include "Util/Color.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/SpriteSheet.hpp"
#include "Util/Text.hpp"
#include <cstddef>
#include <functional>
#include <glm/fwd.hpp>
#include <memory>
#include <vector>

namespace UI {
BattleUIManager::BattleUIManager(EventSystem::BattleSystem &currentBattle)
    : Util::GameObject(),
      m_CurrentBattle(currentBattle) {
    // TODO: This should be dependency injected base on context.
    SetDrawable(std::make_shared<Util::Image>(
        RESOURCE_DIR "/graphics/backgrounds/combat/castle/static_1080.png"));
    LOG_ERROR("zindex of background is {}", GetZIndex());

    BindEvents();
    SetZIndex(-1);
    m_PlayerHpBar = std::make_shared<Utils::Slider>(
        RESOURCE_DIR "/graphics/pack1.png", RESOURCE_DIR "/graphics/pack1.png",
        currentBattle.GetPlayer().first->GetCurrentHealth(), 0,
        currentBattle.GetPlayer().first->GetMaxHealth(), GetZIndex() + 1);
    m_EnemyHpBar = std::make_shared<Utils::Slider>(
        RESOURCE_DIR "/graphics/pack1.png", RESOURCE_DIR "/graphics/pack1.png",
        currentBattle.GetEnemy().first->GetCurrentHealth(), 0,
        currentBattle.GetEnemy().first->GetMaxHealth(), GetZIndex() + 1);

    AddChild(m_EnemyEffectBar);
    AddChild(m_PlayerEffectBar);

    SetupEndTurnBtn();

    SetBattleBarInform(m_PlayerHpBar,
                       currentBattle.GetPlayer().first->GetName(), {-475, -350},
                       {.5, .5});
    SetBattleBarInform(m_EnemyHpBar, currentBattle.GetEnemy().first->GetName(),
                       {475, 400}, {.5, .5});

    SetCardRenderer(m_PlayerCardRenderers,
                    currentBattle.GetPlayer().first->GetCardMap());
    SetCardRenderer(m_EnemyCardRenderers,
                    currentBattle.GetEnemy().first->GetCardMap());

    for (auto cardRender : m_PlayerCardRenderers) {
        AddChild(cardRender);
    }
    for (auto cardRender : m_EnemyCardRenderers) {
        AddChild(cardRender);
        cardRender->SetCardVisible(false);
    }
    m_EnemyEffectBar->SetPosition({475, 345});
    m_PlayerEffectBar->SetPosition({-475, -455});
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

void BattleUIManager::Update() {
    auto currentStatus = m_CurrentBattle.GetCurrentRound();

    switch (currentStatus) {
    case EventSystem::BattleRounds::PLAYERTURN:
        for (auto cardRenderer : m_PlayerCardRenderers) {
            for (auto playerDice : m_CurrentBattle.GetPlayer().second) {
                cardRenderer->Use(playerDice, m_CurrentBattle);
            }
        }
        break;
    case EventSystem::BattleRounds::ENEMYTURN:
        for (auto cardRenderer : m_EnemyCardRenderers) {
            for (auto enemyDice : m_CurrentBattle.GetEnemy().second) {
                cardRenderer->Use(enemyDice, m_CurrentBattle);
            }
        }
        break;
    }
}

void BattleUIManager::OnChangeRound(EventSystem::BattleRounds oldStatus,
                                    EventSystem::BattleRounds newStatus) {
    switch (newStatus) {
    case EventSystem::BattleRounds::PLAYERTURN:
        SetEnemyUIVisible(false);
        SetPlayerUIVisible(true);
        break;
    case EventSystem::BattleRounds::ENEMYTURN:
        SetPlayerUIVisible(false);
        SetEnemyUIVisible(true);
        break;
    }
}

void BattleUIManager::SetPlayerUIVisible(bool visible) {
    m_EndTurnBtnIcon->SetVisible(visible);
    m_EndTurnBtnText->SetVisible(visible);
    for (auto cardRenderer : m_PlayerCardRenderers) {
        cardRenderer->SetCardVisible(visible);
    }
}

void BattleUIManager::SetEnemyUIVisible(bool visible) {
    for (auto cardRenderer : m_EnemyCardRenderers) {
        cardRenderer->SetCardVisible(visible);
    }
}

void BattleUIManager::DetectUiClick(const glm::vec2 &pos) {
    if (m_EndTurnBtnIcon->IsOnTop(pos) || m_EndTurnBtnText->IsOnTop(pos)) {
        LOG_ERROR("ChangeStatus");
        m_CurrentBattle.ChangeRound();
    }
    if (m_CurrentBattle.GetCurrentState() == EventSystem::BattleStates::END) {
        if (m_EndBattleBtn != nullptr) {
            if (m_EndBattleBtn->IsOnTop(pos)) {
                m_CurrentBattle.ChangeBackEvent();
            }
        }
    }
}

void BattleUIManager::BindEvents() {

    auto playerEffectChange = std::bind(
        &Utils::EffectBar::ShowEffect, m_PlayerEffectBar, std::placeholders::_1,
        std::placeholders::_2, std::placeholders::_3);
    auto enemyEffectChange = std::bind(
        &Utils::EffectBar::ShowEffect, m_EnemyEffectBar, std::placeholders::_1,
        std::placeholders::_2, std::placeholders::_3);

    m_CurrentBattle.GetPlayer().first->BindOnCurrentHealthChange(
        "PlayerHealthChanged", [this](int oldHealth, int newHealth) {
            m_PlayerHpBar->SetCurrentValue(newHealth);
        });
    m_CurrentBattle.GetPlayer().first->BindOnMaxHealthChange(
        "PlayerMaxHealthChanged", [this](int oldHealth, int newHealth) {
            m_PlayerHpBar->SetMaxValue(newHealth);
        });

    m_CurrentBattle.GetEnemy().first->BindOnCurrentHealthChange(
        "EnemyHealthChanged", [this](int oldHealth, int newHealth) {
            m_EnemyHpBar->SetCurrentValue(newHealth);
        });
    m_CurrentBattle.GetEnemy().first->BindOnMaxHealthChange(
        "EnemyMaxHealthChanged", [this](int oldHealth, int newHealth) {
            m_EnemyHpBar->SetMaxValue(newHealth);
        });

    m_CurrentBattle.GetPlayerEffectSystem()->BindOnEffectChange(
        "UIChange", playerEffectChange);
    m_CurrentBattle.GetEnemyEffectSystem()->BindOnEffectChange(
        "UIChange", enemyEffectChange);
}

void BattleUIManager::SetCardRenderer(
    std::vector<std::shared_ptr<CardsRenderer::CardRenderer>> &cardRenderers,
    const std::vector<std::vector<std::shared_ptr<Cards::Card>>> &cardMap) {
    int xSpace = 50;
    int ySpace = 30;
    int columns = 0;
    bool isNewColumns = false;
    glm::ivec2 cardSize1 = {0, 0};
    std::vector<glm::ivec2> cardPos;
    for (size_t x = 0; x < cardMap.size(); x++) {
        isNewColumns = false;
        for (size_t y = 0; y < cardMap[0].size(); y++) {
            if (cardMap[x][y] != nullptr) {
                if (isNewColumns == false) {
                    columns++;
                    isNewColumns = true;
                }
                auto newCard = std::make_shared<CardsRenderer::CardRenderer>(
                    cardMap[x][y]);
                LOG_ERROR(cardMap[x][y]->GetCardName());
                int cardSize = cardMap[x][y]->GetSize();
                cardRenderers.push_back(newCard);
                cardPos.push_back({x, y});
                if (cardSize == 2) {
                    y++;
                } else if (cardSize == 1) {
                    cardSize1 = newCard->GetScaledSize();
                }
            }
        }
    }
    int cardXDistance = (cardSize1.x + xSpace);
    int width = (columns - 1) * cardXDistance;
    int startXPos = -(width / 2);

    int CardYDistance = (cardSize1.y + ySpace);
    int startYPos = CardYDistance / 2;

    for (size_t i = 0; i < cardPos.size(); i++) {
        int xPos = startXPos + cardPos[i].x * cardXDistance;
        int yPos = cardRenderers[i]->GetSize() == 2
                       ? 0
                       : startYPos - cardPos[i].y * CardYDistance;
        cardRenderers[i]->SetTranslate({xPos, yPos});
    }
}

void BattleUIManager::SetupEndTurnBtn() {
    m_EndTurnBtnIcon = std::make_shared<Util::GameObject>();
    m_EndTurnBtnText = std::make_shared<Util::GameObject>();
    auto endTurnSprite =
        std::make_shared<Util::SpriteSheet>(RESOURCE_DIR "/graphics/pack1.png");
    endTurnSprite->SetDrawRect({1863, 219, 161, 219});
    m_EndTurnBtnIcon->SetDrawable(endTurnSprite);
    m_EndTurnBtnText->SetDrawable(
        std::make_shared<Util::Text>(RESOURCE_DIR "/NotoSans-Bold.ttf", 30,
                                     "END TURN", Util::Color(255, 255, 255)));
    m_EndTurnBtnIcon->m_Transform.translation = {860, -400};
    m_EndTurnBtnIcon->m_Transform.scale = {0.5, 0.5};
    m_EndTurnBtnText->m_Transform.translation = {860, -465};

    AddChild(m_EndTurnBtnIcon);
    AddChild(m_EndTurnBtnText);
}

void BattleUIManager::ShowPlayerWinUI(int coin, int giveExp, int nextLevelExp,
                                      int currentExp) {
    for (auto child : GetChildren()) {
        child->SetVisible(false);
    }
    auto winUi = std::make_shared<Util::GameObject>();
    winUi->SetDrawable(
        std::make_shared<Util::Image>(RESOURCE_DIR "/EndBattleYouWIN.png"));
    winUi->m_Transform.scale = {0.75, 0.75};
    winUi->m_Transform.translation = {0, winUi->GetScaledSize().y / 2};
    winUi->SetZIndex(GetZIndex() + 1);

    auto coinUi = std::make_shared<Util::GameObject>();
    coinUi->SetZIndex(GetZIndex() + 1);
    coinUi->m_Transform.scale = {0.75, 0.75};
    coinUi->m_Transform.translation = {-680, 0};
    coinUi->SetDrawable(
        std::make_shared<Util::Image>(RESOURCE_DIR "/EndBattleCoinGive.png"));

    auto expUi = std::make_shared<Util::GameObject>();
    auto expText = std::make_shared<Util::Text>(
        RESOURCE_DIR "/NotoSans-Bold.ttf", 72, "x" + std::to_string(giveExp),
        Util::Color(255, 242, 47));
    expUi->SetZIndex(GetZIndex() + 1);
    expUi->m_Transform.scale = {0.75, 0.75};
    expUi->m_Transform.translation = {680, 0};
    expUi->SetDrawable(
        std::make_shared<Util::Image>(RESOURCE_DIR "/EndBattleExpGive.png"));
    expUi->AddChild(std::make_shared<Util::GameObject>());
    expUi->GetChildren()[0]->SetDrawable(expText);
    expUi->GetChildren()[0]->m_Transform.translation = {775, 0};
    expUi->GetChildren()[0]->SetZIndex(GetZIndex() + 2);

    m_EndBattleBtn = std::make_shared<Util::GameObject>();
    m_EndBattleBtn->SetDrawable(
        std::make_shared<Util::Image>(RESOURCE_DIR "/EndBattleBtn.png"));
    m_EndBattleBtn->SetZIndex(GetZIndex() + 1);
    m_EndBattleBtn->m_Transform.scale = {0.75, 0.75};
    m_EndBattleBtn->m_Transform.translation = {0, -450};

    auto nextLevelText = std::make_shared<Util::Text>(
        RESOURCE_DIR "/NotoSans-Bold.ttf", 40,
        "Next Level: " + std::to_string(currentExp) + "/" +
            std::to_string(nextLevelExp),
        Util::Color(255, 242, 47));

    auto nextLevelUi = std::make_shared<Util::GameObject>();
    nextLevelUi->SetDrawable(nextLevelText);
    nextLevelUi->SetZIndex(GetZIndex() + 1);
    nextLevelUi->m_Transform.translation = {0, -200};

    // Unbind Should not be here.
    m_CurrentBattle.GetPlayer().first->UnBindOnCurrentHealthChange(
        "PlayerHealthChanged");
    m_CurrentBattle.GetPlayer().first->UnBindOnMaxHealthChange(
        "PlayerMaxHealthChanged");

    m_CurrentBattle.GetEnemy().first->UnBindOnCurrentHealthChange(
        "EnemyHealthChanged");
    m_CurrentBattle.GetEnemy().first->UnBindOnMaxHealthChange(
        "EnemyMaxHealthChanged");

    AddChild(winUi);
    AddChild(coinUi);
    AddChild(expUi);
    AddChild(m_EndBattleBtn);
    AddChild(nextLevelUi);
};
void BattleUIManager::ShowEnemyWinUI() {

};

} // namespace UI
