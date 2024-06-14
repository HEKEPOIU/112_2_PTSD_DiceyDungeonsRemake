
#ifndef CARDS_VARIANT_SnakeEyeChard_HPP
#define CARDS_VARIANT_SnakeEyeChard_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/TotalRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
namespace Cards::Variant {
class SnakeEyeChard : public Cards::Card {
public:
    SnakeEyeChard()
        : Cards::Card(16, 1) {
        m_CardDescription = "Roll 2 ones";
        m_CardName = "SNAKE EYE CHARM";
        m_Color = Cards::CardColor::RED;
        AddRequireSlot(
            std::make_shared<RequireVariant::TotalRequire>(*this, 6));
    };

    virtual void ResetToDefault() override { m_Current = 0; };

    virtual void Use(EventSystem::BattleSystem &currentBattle) override {
        if (!IsFit()) {
            return;
        }
        m_Current += m_CardRequireSlot[0]->GetContainDice()->GetNum();
        currentBattle.RemoveDice(m_CardRequireSlot[0]->GetContainDice());

        if (m_Current >= m_MaxNum) {
            // I Think this weird.
            currentBattle.UseCard(
                [this](EventSystem::BattleSystem &currentBattle) {

                });
            currentBattle.RemoveDice(m_CardRequireSlot[0]->GetContainDice());
            for (auto event : m_OnCardUsed) {
                event.second();
            }
            currentBattle.RollDice(1);
            currentBattle.RollDice(1);
            m_Current = 0;
        }
    };

private:
    int m_MaxNum = 6;
    int m_Current = 0;
};
} // namespace Cards::Variant

#endif
