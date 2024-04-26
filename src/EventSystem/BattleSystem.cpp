#include "EventSystem/BattleSystem.hpp"
#include "Character/PlayerDice.hpp"
#include "EventSystem/BaseEventSystem.hpp"
#include "EventSystem/EffectSystem.hpp"
#include "Player/PlayerBattleInput.hpp"
#include <memory>
#include <random>

namespace EventSystem {
BattleSystem::BattleSystem(std::shared_ptr<GameCore::MainGame> mainGame,
                           std::shared_ptr<Character::BaseCharacter> player,
                           std::shared_ptr<Character::BaseCharacter> target)
    : BaseEventSystem(mainGame),
      m_Player(player, {}),
      m_Enemy(target, {}) {
    m_PlayerInput = std::make_shared<Player::PlayerBattleInput>();
    m_UIManager = std::make_shared<UI::BattleUIManager>(*this);

    m_Player.first->BindOnCurrentHealthChange(
        "OnPlayerDead", [this](int oldValue, int newValue) {
            if (newValue <= 0) {
                ChangeStatus(BattleStates::END);
                for (auto dice : m_Player.second) {
                    RemoveChild(dice);
                }
                for (auto dice : m_Enemy.second) {
                    RemoveChild(dice);
                }
                m_Player.second.clear();
                m_Enemy.second.clear();
                RemoveChild(m_Player.first);
                RemoveChild(m_Enemy.first);
                m_UIManager->ShowEnemyWinUI();
            }
        });
    m_Enemy.first->BindOnCurrentHealthChange(
        "OnEnemyDead", [this](int oldValue, int newValue) {
            if (newValue <= 0) {
                ChangeStatus(BattleStates::END);
                for (auto dice : m_Player.second) {
                    RemoveChild(dice);
                }
                for (auto dice : m_Enemy.second) {
                    RemoveChild(dice);
                }
                m_Player.second.clear();
                m_Enemy.second.clear();
                auto player = std::dynamic_pointer_cast<Character::PlayerDice>(
                    m_Player.first);
                player->SetExp(player->GetExp() + m_Enemy.first->GetLevel());
                RemoveChild(m_Player.first);
                RemoveChild(m_Enemy.first);
                m_UIManager->ShowPlayerWinUI(1, m_Enemy.first->GetLevel(),
                                             player->GetCurrentLevelUpArr(),
                                             player->GetExp());
            }
        });

    AddChild(m_UIManager);
    AddChild(m_Player.first);
    AddChild(m_Enemy.first);
}

BattleSystem::~BattleSystem() {
    m_Player.first->UnBindOnCurrentHealthChange("OnPlayerDead");
    m_Enemy.first->UnBindOnCurrentHealthChange("OnEnemyDead");
}

void BattleSystem::EventStart() {
    m_Player.first->SetBattlePosition();
    m_Enemy.first->SetBattlePosition();
    m_Player.first->RoundStart(*this);
    ChangeStatus(BattleStates::UPDATE);
}
void BattleSystem::EventUpdate() {
    m_PlayerInput->InputUpdate(*this);
    if (m_CurrentState != BattleStates::UPDATE) {
        return;
    }

    switch (m_CurrentRound) {
    case (BattleRounds::PLAYERTURN):
        m_Player.first->RoundUpdate(*this);
        break;
    case (BattleRounds::ENEMYTURN):
        m_Enemy.first->RoundUpdate(*this);
        break;
    }
}
void BattleSystem::EventEnd() {}

void BattleSystem::RollDice(unsigned short target) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned short> dis(1, 6);

    auto newDice = std::make_shared<DiceUtils::Dice>(dis(gen));
    if (target != 0) {
        newDice->SetNum(target);
    }
    SetUpDice(newDice);
}

void BattleSystem::RemoveDice(const std::shared_ptr<DiceUtils::Dice> &dice) {
    // We Can't use auto here because it will copy the value.
    std::vector<std::shared_ptr<DiceUtils::Dice>> &diceVector =
        m_CurrentRound == BattleRounds::PLAYERTURN ? m_Player.second
                                                   : m_Enemy.second;

    auto removeIter = std::remove(diceVector.begin(), diceVector.end(), dice);
    if (removeIter != diceVector.end()) {
        diceVector.erase(removeIter, diceVector.end());
        RemoveChild(dice);
    }
}

void BattleSystem::ChangeRound() {

    for (auto dice : m_Player.second) {
        RemoveDice(dice);
    }
    for (auto dice : m_Enemy.second) {
        RemoveDice(dice);
    }
    m_Player.second.clear();
    m_Enemy.second.clear();

    BattleRounds oldStatus = m_CurrentRound;
    switch (m_CurrentRound) {
    case (BattleRounds::PLAYERTURN):
        m_CurrentRound = BattleRounds::ENEMYTURN;
        m_Player.first->RoundEnd(*this);
        m_Enemy.first->RoundStart(*this);
        m_EnemyEffectSystem->EffectUpdate();
        m_PlayerEffectSystem->EffectUpdate();
        break;
    case (BattleRounds::ENEMYTURN):
        m_CurrentRound = BattleRounds::PLAYERTURN;
        m_Enemy.first->RoundEnd(*this);
        m_Player.first->RoundStart(*this);
        m_EnemyEffectSystem->EffectUpdate();
        m_PlayerEffectSystem->EffectUpdate();
        break;
    }

    m_UIManager->OnChangeRound(oldStatus, m_CurrentRound);
};
void BattleSystem::SetUpDice(const std::shared_ptr<DiceUtils::Dice> &dice) {
    dice->SetZIndex(10);
    AddChild(dice);
    switch (m_CurrentRound) {
    case (BattleRounds::PLAYERTURN):
        m_Player.second.push_back(dice);
        dice->SetPosition({-300 + (int)m_Player.second.size() * 150, -350});
        break;
    case (BattleRounds::ENEMYTURN):
        m_Enemy.second.push_back(dice);
        dice->SetPosition({300 + (int)m_Enemy.second.size() * -150, 450});
        break;
    }
};

void BattleSystem::UseDice() {
    m_UIManager->Update();
}

void BattleSystem::DetectUiClick(const glm::vec2 &pos) {
    m_UIManager->DetectUiClick(pos);
}

void BattleSystem::ApplyDamage(std::shared_ptr<Character::BaseCharacter> target,
                               int damage) {
    std::unique_ptr<EffectSystem> &effectSystem =
        target == m_Player.first ? m_PlayerEffectSystem : m_EnemyEffectSystem;
    int shieldAmount =
        effectSystem->GetEffectAmount(EffectSystem::BattleEffect::SHIELD);
    effectSystem->ApplyEffect(EffectSystem::BattleEffect::SHIELD, -damage);
    damage = glm::max(damage - shieldAmount, 0);

    target->ModifyCurrentHealth(-damage);
}

void BattleSystem::ApplyEffect(std::shared_ptr<Character::BaseCharacter> target,
                               EventSystem::EffectSystem::BattleEffect effect,
                               int shield) {
    std::unique_ptr<EffectSystem> &effectSystem =
        target == m_Player.first ? m_PlayerEffectSystem : m_EnemyEffectSystem;
    effectSystem->ApplyEffect(effect, shield);
}

void BattleSystem::UseCard(
    std::function<void(EventSystem::BattleSystem &)> func) {
    func(*this);
}

void BattleSystem::ChangeStatus(BattleStates state) {
    if (m_CurrentState == state) {
        return;
    }
    m_CurrentState = state;
}

} // namespace EventSystem
