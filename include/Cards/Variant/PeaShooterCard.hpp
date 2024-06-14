
#ifndef CARDS_VARIANT_PeaShooterCard_HPP
#define CARDS_VARIANT_PeaShooterCard_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/MaxRequire.hpp"
#include "Cards/RequireVariant/TotalRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
namespace Cards::Variant {
class PeaShooterCard : public Cards::Card {
public:
    PeaShooterCard()
        : Cards::Card(8, 1) {
        m_CardDescription = "Do 2 damage (Reuseable)";
        m_CardName = "PEA SHOOTER";
        m_Color = Cards::CardColor::RED;
        AddRequireSlot(
            std::make_shared<RequireVariant::TotalRequire>(*this, 5));
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
            currentBattle.UseCard(
                [this](EventSystem::BattleSystem &currentBattle) {
                    switch (currentBattle.GetCurrentRound()) {

                    case EventSystem::BattleRounds::PLAYERTURN:
                        currentBattle.ApplyDamage(
                            currentBattle.GetEnemy().first, (2));
                        break;
                    case EventSystem::BattleRounds::ENEMYTURN:
                        currentBattle.ApplyDamage(
                            currentBattle.GetPlayer().first, (2));
                        break;
                    }
                });
            m_Current = 0;
        }
    };

private:
    int m_MaxNum = 5;
    int m_Current = 0;
};
} // namespace Cards::Variant

#endif
