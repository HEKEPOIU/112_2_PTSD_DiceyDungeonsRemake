
#ifndef CARDS_VARIANT_SpatulaCard_HPP
#define CARDS_VARIANT_SpatulaCard_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/NoneRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
namespace Cards::Variant {
class SpatulaCard : public Cards::Card {
public:
    SpatulaCard()
        : Cards::Card(15, 1) {
        m_CardDescription = "Flip a dice upside down";
        m_CardName = "SPATULA";
        m_Color = Cards::CardColor::GREEN;
        AddRequireSlot(std::make_shared<RequireVariant::NoneRequire>(*this));
    };

    virtual void Use(EventSystem::BattleSystem &currentBattle) override {
        if (!IsFit()) {
            return;
        }

        // I Think this weird.
        currentBattle.UseCard(
            [this](EventSystem::BattleSystem &currentBattle) {});
        auto dice = m_CardRequireSlot[0]->GetContainDice();

        dice->SetNum(7 - dice->GetNum());

        for (auto event : m_OnCardUsed) {
            event.second();
        }
    };
};
} // namespace Cards::Variant

#endif
