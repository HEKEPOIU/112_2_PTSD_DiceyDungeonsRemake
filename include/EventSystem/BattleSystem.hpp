#ifndef EVENTSYSTEM_BATTLESYSTEM_HPP
#define EVENTSYSTEM_BATTLESYSTEM_HPP

#include "Character/BaseCharacter.hpp"
#include "DiceUtils/Dice.hpp"
#include "EventSystem/BaseEventSystem.hpp"
#include "Player/PlayerBattleInput.hpp"
#include "UI/UIManager.hpp"
#include <memory>
#include <utility>
namespace EventSystem {
class BattleSystem : public BaseEventSystem {

public:
    enum class CurrentStatus {
        PLAYERTURN,
        ENEMYTURN,
    };

    BattleSystem(std::shared_ptr<GameCore::MainGame> mainGame,
                 std::shared_ptr<Character::BaseCharacter> player,
                 std::shared_ptr<Character::BaseCharacter> target);

    std::pair<std::shared_ptr<Character::BaseCharacter>,
              std::vector<std::shared_ptr<DiceUtils::Dice>>> &
    GetPlayer() {
        return m_Player;
    };
    std::pair<std::shared_ptr<Character::BaseCharacter>,
              std::vector<std::shared_ptr<DiceUtils::Dice>>> &
    GetEnemy() {
        return m_Enemy;
    }

    void RollDice(unsigned short target = 0);
    void SetUpDice(std::shared_ptr<DiceUtils::Dice> dice);
    virtual void EventStart() override;
    virtual void EventUpdate() override;
    virtual void EventEnd() override;

private:
    std::pair<std::shared_ptr<Character::BaseCharacter>,
              std::vector<std::shared_ptr<DiceUtils::Dice>>>
        m_Player;
    std::pair<std::shared_ptr<Character::BaseCharacter>,
              std::vector<std::shared_ptr<DiceUtils::Dice>>>
        m_Enemy;
    std::shared_ptr<Player::PlayerBattleInput> m_PlayerInput;
    std::shared_ptr<UI::UIManager> m_UIManager;
    CurrentStatus m_CurrentStates = CurrentStatus::PLAYERTURN;
};
} // namespace EventSystem

#endif
