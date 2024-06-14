
#ifndef CARDS_VARIANT_BattleAxeCard_HPP
#define CARDS_VARIANT_BattleAxeCard_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/MaxRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
namespace Cards::Variant {
class BattleAxeCard : public Cards::Card {
public:
    BattleAxeCard()
        : Cards::Card(5, 1) {
        m_CardDescription = "Do 2x[] damage";
        m_CardName = "BATTLE AXE";
        m_Color = Cards::CardColor::ORANGE;
        AddRequireSlot(std::make_shared<RequireVariant::MaxRequire>(*this, 4));
    };
    virtual void Use(EventSystem::BattleSystem &currentBattle) override {
        if (!IsFit()) {
            return;
        }

        // I Think this weird.
        currentBattle.UseCard([this](EventSystem::BattleSystem &currentBattle) {
            int num = m_CardRequireSlot[0]->GetContainDiceNum();
            switch (currentBattle.GetCurrentRound()) {

            case EventSystem::BattleRounds::PLAYERTURN:
                currentBattle.ApplyDamage(currentBattle.GetEnemy().first,
                                          (num * 2));

                break;
            case EventSystem::BattleRounds::ENEMYTURN:
                currentBattle.ApplyDamage(currentBattle.GetPlayer().first,
                                          (num * 2));
                break;
            }
        });
        currentBattle.RemoveDice(m_CardRequireSlot[0]->GetContainDice());
        for (auto event : m_OnCardUsed) {
            event.second();
        }
    };
};
} // namespace Cards::Variant

#endif
