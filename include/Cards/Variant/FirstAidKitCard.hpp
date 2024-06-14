
#ifndef CARDS_VARIANT_FirstAidKitCard_HPP
#define CARDS_VARIANT_FirstAidKitCard_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/TotalRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
namespace Cards::Variant {
class FirstAidKitCard : public Cards::Card {
public:
    FirstAidKitCard()
        : Cards::Card(18, 1) {
        m_CardDescription = "Heal 8 health";
        m_CardName = "FIRST AID KIT";
        m_Color = Cards::CardColor::RED;
        AddRequireSlot(
            std::make_shared<RequireVariant::TotalRequire>(*this, 16));
    };

    virtual void ResetToDefault() override { m_Current = 0; };

    virtual void Use(EventSystem::BattleSystem &currentBattle) override {
        if (!IsFit()) {
            return;
        }
        m_Current += m_CardRequireSlot[0]->GetContainDice()->GetNum();
        currentBattle.RemoveDice(m_CardRequireSlot[0]->GetContainDice());

        if (m_Current >= m_MaxNum) {
            // I Think this weird.
            switch (currentBattle.GetCurrentRound()) {

            case EventSystem::BattleRounds::PLAYERTURN:
                currentBattle.GetPlayer().first->SetCurrentHealth(8);
                break;
            case EventSystem::BattleRounds::ENEMYTURN:
                currentBattle.GetEnemy().first->SetCurrentHealth(8);
                break;
            }
            m_Current = 0;
            for (auto event : m_OnCardUsed) {
                event.second();
            }
        }
    };

private:
    int m_MaxNum = 16;
    int m_Current = 0;
};
} // namespace Cards::Variant

#endif
