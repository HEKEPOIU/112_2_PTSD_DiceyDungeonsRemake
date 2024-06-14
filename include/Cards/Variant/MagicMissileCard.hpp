
#ifndef CARDS_VARIANT_MagicMissileCard_HPP
#define CARDS_VARIANT_MagicMissileCard_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/EvenRequire.hpp"
#include "Cards/RequireVariant/MaxRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
namespace Cards::Variant {
class MagicMissileCard : public Cards::Card {
public:
    MagicMissileCard()
        : Cards::Card(19, 1) {
        m_CardDescription = "Do 5 damage";
        m_CardName = "MAGIC MISSILE";
        m_Color = Cards::CardColor::ORANGE;
        AddRequireSlot(std::make_shared<RequireVariant::EvenRequire>(*this));
    };
    virtual bool CanUse() override { return !m_IsUsed; }
    virtual void ResetToDefault() override { m_IsUsed = false; }

    virtual void Use(EventSystem::BattleSystem &currentBattle) override {
        if (!IsFit()) {
            return;
        }

        currentBattle.UseCard([this](EventSystem::BattleSystem &currentBattle) {
            int num = m_CardRequireSlot[0]->GetContainDiceNum();
            switch (currentBattle.GetCurrentRound()) {

            case EventSystem::BattleRounds::PLAYERTURN:
                currentBattle.ApplyDamage(currentBattle.GetEnemy().first, (5));
                break;
            case EventSystem::BattleRounds::ENEMYTURN:
                currentBattle.ApplyDamage(currentBattle.GetPlayer().first, (5));
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
