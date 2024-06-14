
#ifndef CARDS_VARIANT_CombatRollSkill_HPP
#define CARDS_VARIANT_CombatRollSkill_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/NoneRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
#include <iostream>
namespace Cards::Variant {
class CombatRollSkill : public Cards::Card {
public:
    CombatRollSkill()
        : Cards::Card(-1, 2) {
        m_CardDescription = "Reroll a dice    (3 uses this turn)";
        m_CardName = "COMBAT ROLL";
        m_Color = Cards::CardColor::ORANGE;
        AddRequireSlot(std::make_shared<RequireVariant::NoneRequire>(*this));
    };
    virtual void ResetCard() override { maxUseCount = 3; }

    virtual void Use(EventSystem::BattleSystem &currentBattle) override {
        if (!IsFit()) {
            std::cout << "Not Fit" << std::endl;
            return;
        }

        // I Think this weird.
        currentBattle.UseCard([](EventSystem::BattleSystem &currentBattle) {});
        maxUseCount--;
        currentBattle.RemoveDice(m_CardRequireSlot[0]->GetContainDice());
        currentBattle.RollDice();
        if (maxUseCount == 0) {
            for (auto event : m_OnCardUsed) {
                event.second();
            }
            maxUseCount = 3;
        }
    };

private:
    int maxUseCount = 3;
};
} // namespace Cards::Variant

#endif
