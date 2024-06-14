#ifndef AI_ENEMYAI_HPP
#define AI_ENEMYAI_HPP

#include "DiceUtils/Dice.hpp"
#include "DiceUtils/Timer.hpp"
#include "EventSystem/BattleSystem.hpp"
#include "Util/Logger.hpp"
#include <memory>
#include <utility>
namespace AI {
class EnemyAI {
public:
    EnemyAI() {
        m_ActionSpacingTimer->SetOnTimerEnd([this]() { isWaiting = false; });
    };

    ~EnemyAI() { m_ActionSpacingTimer->RemoveOnTimerEnd(); };

    void RoundStart() { StartDelay(); }
    virtual void RoundUpdate(EventSystem::BattleSystem &currentBattle) {
        m_ActionSpacingTimer->Update();
    };

protected:
    const std::pair<std::shared_ptr<UI::CardsRenderer::RequireSlotRenderer>,
                    std::shared_ptr<DiceUtils::Dice>>
    GetAvailableCard(EventSystem::BattleSystem &currentBattle) {
        auto dices = currentBattle.GetEnemy().second;
        auto cards = currentBattle.GetEnemyCardRenderer();
        for (auto dice : dices) {
            if (!dice->GetVisible()) {
                continue;
            }
            for (auto card : cards) {
                if (!card->GetVisible()) {
                    continue;
                }
                auto slot = card->GetFitSlot(dice);
                if (slot != nullptr) {
                    return {slot, dice};
                }
            }
        }
        return {nullptr, nullptr};
    };

    void UseDice(std::shared_ptr<UI::CardsRenderer::RequireSlotRenderer> &card,
                 std::shared_ptr<DiceUtils::Dice> &dice,
                 EventSystem::BattleSystem &currentBattle) {
        card->Use(dice, currentBattle);
    };

    void StartDelay() {
        m_ActionSpacingTimer->StartTimer();
        isWaiting = true;
    }
    bool isWaiting = false;

private:
    std::unique_ptr<DiceUtils::Timer> m_ActionSpacingTimer =
        std::make_unique<DiceUtils::Timer>(1);
};
} // namespace AI

#endif
