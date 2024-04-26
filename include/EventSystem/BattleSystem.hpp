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
enum class BattleRounds {
    PLAYERTURN,
    ENEMYTURN,
};

enum class BattleStates {
    START,
    UPDATE,
    END,
};

// I thing this class have too much responsibilities.
class BattleSystem : public BaseEventSystem {

public:
    BattleSystem(std::shared_ptr<GameCore::MainGame> mainGame,
                 std::shared_ptr<Character::BaseCharacter> player,
                 std::shared_ptr<Character::BaseCharacter> target);
    ~BattleSystem();

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

    const BattleRounds &GetCurrentRound() const { return m_CurrentRound; }
    const BattleStates &GetCurrentState() const { return m_CurrentState; }

    void RollDice(unsigned short target = 0);
    void RemoveDice(const std::shared_ptr<DiceUtils::Dice> &dice);
    void SetUpDice(const std::shared_ptr<DiceUtils::Dice> &dice);
    void ChangeRound();
    void ChangeStatus(BattleStates state);
    void UseDice();
    void DetectUiClick(const glm::vec2 &pos);
    void ApplyDamage(std::shared_ptr<Character::BaseCharacter> target,
                     int damage);
    void ApplyEffect(std::shared_ptr<Character::BaseCharacter> target,
                     EventSystem::EffectSystem::BattleEffect effect,
                     int shield);

    void UseCard(std::function<void(EventSystem::BattleSystem &)> func);
    const std::unique_ptr<EffectSystem> &GetPlayerEffectSystem() {
        return m_PlayerEffectSystem;
    }
    const std::unique_ptr<EffectSystem> &GetEnemyEffectSystem() {
        return m_EnemyEffectSystem;
    }
    virtual void EventStart() override;
    virtual void EventUpdate() override;
    virtual void EventEnd() override;
    std::vector<std::shared_ptr<UI::CardsRenderer::CardRenderer>> &
    GetEnemyCardRenderer() {
        return m_UIManager->GetEnemyCardRenderer();
    }

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

    std::shared_ptr<UI::BattleUIManager> m_UIManager;
    std::shared_ptr<Player::PlayerBattleInput> m_PlayerInput;
    BattleRounds m_CurrentRound = BattleRounds::PLAYERTURN;
    BattleStates m_CurrentState = BattleStates::START;
};
} // namespace EventSystem

#endif
