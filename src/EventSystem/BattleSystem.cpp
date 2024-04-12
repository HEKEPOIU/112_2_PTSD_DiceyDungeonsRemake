#include "EventSystem/BattleSystem.hpp"
#include "EventSystem/BaseEventSystem.hpp"
#include "EventSystem/EffectSystem.hpp"
#include "Player/PlayerBattleInput.hpp"
#include "Util/Logger.hpp"
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

    AddChild(m_UIManager);
}

void BattleSystem::EventStart() {
    m_Player.first->SetBattlePosition();
    m_Enemy.first->SetBattlePosition();
    m_Player.first->RoundStart(*this);
    ApplyShield(m_Enemy.first, 2);
}
void BattleSystem::EventUpdate() {
    switch (m_CurrentStates) {
    case (BattleStatus::PLAYERTURN):
        m_PlayerInput->InputUpdate(*this);
        m_Player.first->RoundUpdate(*this);
        break;
    case (BattleStatus::ENEMYTURN):
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
    auto diceVector = m_CurrentStates == BattleStatus::PLAYERTURN
                          ? m_Player.second
                          : m_Enemy.second;

    auto removeIter = std::remove(diceVector.begin(), diceVector.end(), dice);
    if (removeIter != diceVector.end()) {
        diceVector.erase(removeIter, diceVector.end());
        RemoveChild(dice);
    }
}

void BattleSystem::ChangeStates() {

    for (auto dice : m_Player.second) {
        RemoveChild(dice);
    }
    for (auto dice : m_Enemy.second) {
        RemoveChild(dice);
    }
    m_Player.second.clear();
    m_Enemy.second.clear();

    BattleStatus oldStatus = m_CurrentStates;
    switch (m_CurrentStates) {
    case (BattleStatus::PLAYERTURN):
        m_CurrentStates = BattleStatus::ENEMYTURN;
        m_Player.first->RoundEnd(*this);
        m_Enemy.first->RoundStart(*this);
        break;
    case (BattleStatus::ENEMYTURN):
        m_CurrentStates = BattleStatus::PLAYERTURN;
        m_Enemy.first->RoundEnd(*this);
        m_Player.first->RoundStart(*this);
        break;
    }

    m_UIManager->OnChangeStatus(oldStatus, m_CurrentStates);
};
void BattleSystem::SetUpDice(const std::shared_ptr<DiceUtils::Dice> &dice) {
    dice->SetZIndex(10);
    AddChild(dice);
    switch (m_CurrentStates) {
    case (BattleStatus::PLAYERTURN):
        m_Player.second.push_back(dice);
        dice->SetPosition({-300 + (int)m_Player.second.size() * 150, -350});
        break;
    case (BattleStatus::ENEMYTURN):
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
    effectSystem->RemoveEffectAmount(EffectSystem::BattleEffect::SHIELD,
                                     damage);

    damage = glm::max(damage - shieldAmount, 0);
    target->ModifyCurrentHealth(-damage);
}

void BattleSystem::ApplyShield(std::shared_ptr<Character::BaseCharacter> target,
                               int shield) {
    std::unique_ptr<EffectSystem> &effectSystem =
        target == m_Player.first ? m_PlayerEffectSystem : m_EnemyEffectSystem;
    effectSystem->ApplyEffect(EffectSystem::BattleEffect::SHIELD, shield);
}

void BattleSystem::UseCard(
    std::function<void(EventSystem::BattleSystem &)> func) {
    func(*this);
}

} // namespace EventSystem
