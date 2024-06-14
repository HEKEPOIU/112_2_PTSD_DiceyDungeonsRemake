
#ifndef CARDS_VARIANT_BumpCard_HPP
#define CARDS_VARIANT_BumpCard_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/NoneRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
namespace Cards::Variant {
class BumpCard : public Cards::Card {
public:
    BumpCard()
        : Cards::Card(14, 1) {
        m_CardDescription = "Dice value +1";
        m_CardName = "BUMP";
        m_Color = Cards::CardColor::RED;
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
        int newDiceNum = dice->GetNum() + 1;
        if (newDiceNum > 6) {
            currentBattle.RollDice(1);
            dice->SetNum(dice->GetNum());
        } else {
            dice->SetNum(dice->GetNum() + 1);
        }

        for (auto event : m_OnCardUsed) {
            event.second();
        }
    };
};
} // namespace Cards::Variant

#endif
