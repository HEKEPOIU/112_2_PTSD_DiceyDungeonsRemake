
#ifndef CARDS_VARIANT_SixShooterCard_HPP
#define CARDS_VARIANT_SixShooterCard_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/NeedRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
#include <iostream>
namespace Cards::Variant {
class SixShooterCard : public Cards::Card {
public:
    SixShooterCard()
        : Cards::Card(6, 2) {
        m_CardDescription = "Do [] damage\n    (3 uses this turn)";
        m_CardName = "SIX SHOOTER";
        m_Color = Cards::CardColor::ORANGE;
        AddRequireSlot(std::make_shared<RequireVariant::NeedRequire>(*this, 6));
    };
    virtual void ResetCard() override { maxUseCount = 3; }
    virtual void Use(EventSystem::BattleSystem &currentBattle) override {
        if (!IsFit()) {
            std::cout << "Not Fit" << std::endl;
            return;
        }

        // I Think this weird.
        currentBattle.UseCard([this](EventSystem::BattleSystem &currentBattle) {
            int num = m_CardRequireSlot[0]->GetContainDiceNum();
            switch (currentBattle.GetCurrentRound()) {

            case EventSystem::BattleRounds::PLAYERTURN:
                currentBattle.ApplyDamage(currentBattle.GetEnemy().first,
                                          (num));

                break;
            case EventSystem::BattleRounds::ENEMYTURN:
                currentBattle.ApplyDamage(currentBattle.GetPlayer().first,
                                          (num));
                break;
            }
        });
        maxUseCount--;
        currentBattle.RemoveDice(m_CardRequireSlot[0]->GetContainDice());
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
