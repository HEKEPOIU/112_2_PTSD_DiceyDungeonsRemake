
#ifndef CARDS_VARIANT_CRYSTALSWORD_HPP
#define CARDS_VARIANT_CRYSTALSWORD_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/MaxRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
namespace Cards::Variant {
class CrystalSwordCard : public Cards::Card {
public:
    CrystalSwordCard()
        : Cards::Card(7, 2) {
        m_CardDescription = "Do 3x[] damage (once per battle)";
        m_CardName = "CRYSTAL SWORD";
        m_Color = Cards::CardColor::RED;
        AddRequireSlot(std::make_shared<RequireVariant::MaxRequire>(*this, 5));
    };
    virtual bool CanUse() override { return !m_IsUsed; }
    virtual void ResetToDefault() override { m_IsUsed = false; }

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
                                          (num * 3));
                break;
            case EventSystem::BattleRounds::ENEMYTURN:
                currentBattle.ApplyDamage(currentBattle.GetPlayer().first,
                                          (num * 3));
                break;
            }
        });

        currentBattle.RemoveDice(m_CardRequireSlot[0]->GetContainDice());
        m_IsUsed = true;
        for (auto event : m_OnCardUsed) {
            event.second();
        }
    };

private:
    bool m_IsUsed = false;
};
} // namespace Cards::Variant

#endif
