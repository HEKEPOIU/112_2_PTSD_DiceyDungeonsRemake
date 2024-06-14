
#ifndef CARDS_VARIANT_TargetShieldCard_HPP
#define CARDS_VARIANT_TargetShieldCard_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/MaxRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
namespace Cards::Variant {
class TargetShieldCard : public Cards::Card {
public:
    TargetShieldCard()
        : Cards::Card(12, 1) {
        m_CardDescription = "Add [] to shield";
        m_CardName = "TARGET SHIELD";
        m_Color = Cards::CardColor::RED;
        AddRequireSlot(std::make_shared<RequireVariant::MaxRequire>(*this, 2));
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
                currentBattle.ApplyEffect(
                    currentBattle.GetPlayer().first,
                    EventSystem::EffectSystem::BattleEffect::SHIELD, num);
                break;
            case EventSystem::BattleRounds::ENEMYTURN:
                currentBattle.ApplyEffect(
                    currentBattle.GetEnemy().first,
                    EventSystem::EffectSystem::BattleEffect::SHIELD, num);
                break;
            }
        });
        currentBattle.RemoveDice(m_CardRequireSlot[0]->GetContainDice());
    };
};
} // namespace Cards::Variant

#endif
