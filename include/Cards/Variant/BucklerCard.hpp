
#ifndef CARDS_VARIANT_BucklerCard_HPP
#define CARDS_VARIANT_BucklerCard_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/MaxRequire.hpp"
#include "Cards/RequireVariant/TotalRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
namespace Cards::Variant {
class BucklerCard : public Cards::Card {
public:
    BucklerCard()
        : Cards::Card(13, 1) {
        m_CardDescription = "Add 4 to shield";
        m_CardName = "BUCKLER";
        m_Color = Cards::CardColor::RED;
        std::make_shared<RequireVariant::TotalRequire>(*this, 7);
    };
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
                    int num = m_CardRequireSlot[0]->GetContainDiceNum();

                    switch (currentBattle.GetCurrentRound()) {

                    case EventSystem::BattleRounds::PLAYERTURN:
                        currentBattle.ApplyEffect(
                            currentBattle.GetPlayer().first,
                            EventSystem::EffectSystem::BattleEffect::SHIELD, 4);
                        break;
                    case EventSystem::BattleRounds::ENEMYTURN:
                        currentBattle.ApplyEffect(
                            currentBattle.GetEnemy().first,
                            EventSystem::EffectSystem::BattleEffect::SHIELD, 4);
                        break;
                    }
                });
            currentBattle.RemoveDice(m_CardRequireSlot[0]->GetContainDice());
            m_Current = 0;
        }
    };

private:
    int m_MaxNum = 7;
    int m_Current = 0;
};
} // namespace Cards::Variant

#endif
