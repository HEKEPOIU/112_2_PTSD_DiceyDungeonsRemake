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
}

void BattleSystem::EventStart() {
    m_Player.first->SetBattlePosition();
    m_Enemy.first->SetBattlePosition();
    m_Player.first->RoundStart(*this);
}
void BattleSystem::EventUpdate() {
    switch (m_CurrentStates) {
    case (CurrentStatus::PLAYERTURN):
        m_PlayerInput->InputUpdate(*this);
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

void BattleSystem::SetUpDice(std::shared_ptr<DiceUtils::Dice> dice) {
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
