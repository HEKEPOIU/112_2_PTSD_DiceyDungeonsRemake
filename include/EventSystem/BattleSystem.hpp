#ifndef EVENTSYSTEM_BATTLESYSTEM_HPP
#define EVENTSYSTEM_BATTLESYSTEM_HPP

#include "Character/BaseCharacter.hpp"
#include "DiceUtils/Dice.hpp"
#include "EventSystem/BaseEventSystem.hpp"
#include "EventSystem/EffectSystem.hpp"
#include "Player/PlayerBattleInput.hpp"
#include "UI/BattleUIManager.hpp"
#include <memory>
#include <vector>
namespace EventSystem {
enum class BattleStatus {
    PLAYERTURN,
    ENEMYTURN,
};

// I thing this class have too much responsibilities.
class BattleSystem : public BaseEventSystem {

public:
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

    const BattleStatus &GetCurrentStatus() const { return m_CurrentStates; }

    void RollDice(unsigned short target = 0);
    void RemoveDice(const std::shared_ptr<DiceUtils::Dice> &dice);
    void SetUpDice(const std::shared_ptr<DiceUtils::Dice> &dice);
    void ChangeStates();
    void UseDice();
    void DetectUiClick(const glm::vec2 &pos);
    void ApplyDamage(std::shared_ptr<Character::BaseCharacter> target,
                     int damage);
    void ApplyShield(std::shared_ptr<Character::BaseCharacter> target,
                     int shield);

    void UseCard(std::function<void(EventSystem::BattleSystem &)> func);
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
    std::unique_ptr<EffectSystem> m_PlayerEffectSystem =
        std::make_unique<EffectSystem>();
    std::unique_ptr<EffectSystem> m_EnemyEffectSystem =
        std::make_unique<EffectSystem>();
    std::shared_ptr<Player::PlayerBattleInput> m_PlayerInput;
    std::shared_ptr<UI::BattleUIManager> m_UIManager;
    BattleStatus m_CurrentStates = BattleStatus::PLAYERTURN;
};
} // namespace EventSystem

#endif
