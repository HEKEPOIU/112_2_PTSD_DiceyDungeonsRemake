
#ifndef CARDS_VARIANT_BoomerangCard_HPP
#define CARDS_VARIANT_BoomerangCard_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/MaxRequire.hpp"
#include "Cards/RequireVariant/NoneRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
namespace Cards::Variant {
class BoomerangCard : public Cards::Card {
public:
    BoomerangCard()
        : Cards::Card(5, 1) {
        m_CardDescription = "Do 2x[] to enemy,\n\
                        but [] to yourself";
        m_CardName = "BOOMERANG";
        m_Color = Cards::CardColor::ORANGE;
        AddRequireSlot(std::make_shared<RequireVariant::NoneRequire>(*this));
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
                currentBattle.ApplyDamage(currentBattle.GetPlayer().first,
                                          (num));
                break;
            case EventSystem::BattleRounds::ENEMYTURN:
                currentBattle.ApplyDamage(currentBattle.GetPlayer().first,
                                          (num * 2));
                currentBattle.ApplyDamage(currentBattle.GetEnemy().first,
                                          (num));
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
