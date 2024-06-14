
#ifndef CARDS_VARIANT_PirateHookCard_HPP
#define CARDS_VARIANT_PirateHookCard_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/MaxRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
namespace Cards::Variant {
class PirateHookCard : public Cards::Card {
public:
    PirateHookCard()
        : Cards::Card(21, 2) {
        m_CardDescription = "Do [] damage On 4 you can re-use this";
        m_CardName = "PIRATE HOOK";
        m_Color = Cards::CardColor::ORANGE;
        AddRequireSlot(std::make_shared<RequireVariant::MaxRequire>(*this, 5));
    };

    virtual void Use(EventSystem::BattleSystem &currentBattle) override {
        if (!IsFit()) {
            return;
        }
        // if (m_IsUsed) {
        //     for (auto event : m_OnCardUsed) {
        //         event.second();
        //     }
        //     return;
        // }

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
        if (m_CardRequireSlot[0]->GetContainDice()->GetNum() != 4) {
            for (auto event : m_OnCardUsed) {
                event.second();
            }
        }
    };
};
} // namespace Cards::Variant

#endif
