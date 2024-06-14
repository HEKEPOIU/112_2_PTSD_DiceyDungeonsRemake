
#ifndef CARDS_VARIANT_IronShieldCard_HPP
#define CARDS_VARIANT_IronShieldCard_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/MaxRequire.hpp"
#include "Cards/RequireVariant/NoneRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
namespace Cards::Variant {
class IronShieldCard : public Cards::Card {
public:
    IronShieldCard()
        : Cards::Card(11, 2) {
        m_CardDescription = "Add [] shield";
        m_CardName = "IRON SHIELD";
        m_Color = Cards::CardColor::RED;
        AddRequireSlot(std::make_shared<RequireVariant::NoneRequire>(*this));
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
        for (auto event : m_OnCardUsed) {
            event.second();
        }
    };
};
} // namespace Cards::Variant

#endif
