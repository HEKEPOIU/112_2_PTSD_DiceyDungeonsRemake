
#ifndef CARDS_VARIANT_HealingCrystalCard_HPP
#define CARDS_VARIANT_HealingCrystalCard_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/MaxRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
namespace Cards::Variant {
class HealingCrystalCard : public Cards::Card {
public:
    HealingCrystalCard()
        : Cards::Card(17, 2) {
        m_CardDescription = "Recover [] health";
        m_CardName = "HEALING CRYSTAL";
        m_Color = Cards::CardColor::GREEN;
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
                currentBattle.GetPlayer().first->SetCurrentHealth(
                    currentBattle.GetPlayer().first->GetCurrentHealth() + num);
                break;
            case EventSystem::BattleRounds::ENEMYTURN:
                currentBattle.GetEnemy().first->SetCurrentHealth(
                    currentBattle.GetPlayer().first->GetCurrentHealth() + num);
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
