#include "EventSystem/BattleSystem.hpp"
#include "EventSystem/BaseEventSystem.hpp"
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
    AddChild(m_UIManager);
}

void BattleSystem::EventStart() {
    m_Player.first->SetBattlePosition();
    m_Enemy.first->SetBattlePosition();
    m_Player.first->RoundStart(*this);
}
void BattleSystem::EventUpdate() {
    switch (m_CurrentStates) {
    case (CurrentStatus::PLAYERTURN):
        m_UIManager->Update();
        m_PlayerInput->InputUpdate(*this);
        m_Player.first->RoundUpdate(*this);
        break;
    case (CurrentStatus::ENEMYTURN):
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
    switch (m_CurrentStates) {
    case (CurrentStatus::PLAYERTURN):
        m_Player.second.erase(
            std::remove(m_Player.second.begin(), m_Player.second.end(), dice),
            m_Player.second.end());
        break;
    case (CurrentStatus::ENEMYTURN):
        m_Enemy.second.erase(
            std::remove(m_Enemy.second.begin(), m_Enemy.second.end(), dice),
            m_Enemy.second.end());
        break;
    }
}

void BattleSystem::AddCard(
    const std::shared_ptr<UI::CardsRenderer::CardRenderer> &card) {
    m_CardRenderer.push_back(card);
}

void BattleSystem::ChangeStates() {
    switch (m_CurrentStates) {
    case (CurrentStatus::PLAYERTURN):
        m_CurrentStates = CurrentStatus::ENEMYTURN;
        break;
    case (CurrentStatus::ENEMYTURN):
        m_CurrentStates = CurrentStatus::PLAYERTURN;
        break;
    }
    m_CardRenderer.clear();
};
void BattleSystem::SetUpDice(const std::shared_ptr<DiceUtils::Dice> &dice) {
    dice->SetZIndex(10);
    AddChild(dice);
    switch (m_CurrentStates) {
    case (CurrentStatus::PLAYERTURN):
        m_Player.second.push_back(dice);
        dice->SetPosition({-300 + (int)m_Player.second.size() * 150, -350});
        break;
    case (CurrentStatus::ENEMYTURN):
        m_Enemy.second.push_back(dice);
        break;
    }
};

} // namespace EventSystem
