
#ifndef CARDS_VARIANT_MagicShieldCard_HPP
#define CARDS_VARIANT_MagicShieldCard_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/MaxRequire.hpp"
#include "Cards/RequireVariant/NoneRequire.hpp"
#include "Cards/RequireVariant/OddRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
namespace Cards::Variant {
class MagicShieldCard : public Cards::Card {
public:
    MagicShieldCard()
        : Cards::Card(20, 2) {
        m_CardDescription = "Add 3 shield";
        m_CardName = "MAGIC SHIELD";
        m_Color = Cards::CardColor::RED;
        AddRequireSlot(std::make_shared<RequireVariant::OddRequire>(*this));
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
                    EventSystem::EffectSystem::BattleEffect::SHIELD, 3);
                break;
            case EventSystem::BattleRounds::ENEMYTURN:
                currentBattle.ApplyEffect(
                    currentBattle.GetEnemy().first,
                    EventSystem::EffectSystem::BattleEffect::SHIELD, 3);
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
