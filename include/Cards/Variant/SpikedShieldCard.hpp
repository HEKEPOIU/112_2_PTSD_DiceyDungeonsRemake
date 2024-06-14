
#ifndef CARDS_VARIANT_SPIKEDSHIELDCARD_HPP
#define CARDS_VARIANT_SPIKEDSHIELDCARD_HPP

#include "Cards/Card.hpp"
#include "Cards/RequireVariant/MaxRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
namespace Cards::Variant {
class SpikedShieldCard : public Cards::Card {
public:
    SpikedShieldCard()
        : Cards::Card(4, 2) {
        m_CardDescription = "Even [] damage /n odd [] shield";
        m_CardName = "SPIKED SHIELD";
        m_Color = Cards::CardColor::RED;
        AddRequireSlot(std::make_shared<RequireVariant::MaxRequire>(*this, 5));
    };
    virtual void Use(EventSystem::BattleSystem &currentBattle) override {
        if (!IsFit()) {
            return;
        }

        // I Think this weird.
        currentBattle.UseCard([this](EventSystem::BattleSystem &currentBattle) {
            int num = m_CardRequireSlot[0]->GetContainDiceNum();
            if (num % 2 == 0) {
                switch (currentBattle.GetCurrentRound()) {

                case EventSystem::BattleRounds::PLAYERTURN:
                    currentBattle.ApplyDamage(
                        currentBattle.GetEnemy().first,
                        (m_CardRequireSlot[0]->GetContainDiceNum()));
                    break;
                case EventSystem::BattleRounds::ENEMYTURN:
                    currentBattle.ApplyDamage(
                        currentBattle.GetPlayer().first,
                        (m_CardRequireSlot[0]->GetContainDiceNum()));
                    break;
                }
            } else {
                switch (currentBattle.GetCurrentRound()) {

                case EventSystem::BattleRounds::PLAYERTURN:
                    currentBattle.ApplyEffect(
                        currentBattle.GetPlayer().first,
                        EventSystem::EffectSystem::BattleEffect::SHIELD,
                        m_CardRequireSlot[0]->GetContainDiceNum());
                    break;
                case EventSystem::BattleRounds::ENEMYTURN:
                    currentBattle.ApplyEffect(
                        currentBattle.GetEnemy().first,
                        EventSystem::EffectSystem::BattleEffect::SHIELD,
                        m_CardRequireSlot[0]->GetContainDiceNum());
                    break;
                }
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
