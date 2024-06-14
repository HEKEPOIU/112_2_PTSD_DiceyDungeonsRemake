
#ifndef CARDS_VARIANT_JugglingBallCard_HPP
#define CARDS_VARIANT_JugglingBallCard_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/MaxRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
namespace Cards::Variant {
class JugglingBallCard : public Cards::Card {
public:
    JugglingBallCard()
        : Cards::Card(10, 1) {
        m_CardDescription = "Do [] damage get a new dice";
        m_CardName = "JUGGLING BALL";
        m_Color = Cards::CardColor::RED;
        AddRequireSlot(std::make_shared<RequireVariant::MaxRequire>(*this, 3));
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
                                          (num));
                break;
            case EventSystem::BattleRounds::ENEMYTURN:
                currentBattle.ApplyDamage(currentBattle.GetPlayer().first,
                                          (num));
                break;
            }
        });
        currentBattle.RemoveDice(m_CardRequireSlot[0]->GetContainDice());
        currentBattle.RollDice();
        for (auto event : m_OnCardUsed) {
            event.second();
        }
    };
};
} // namespace Cards::Variant

#endif
