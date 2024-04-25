#include "Cards/Variant/SmallShieldCard.hpp"
#include "Cards/Card.hpp"
#include "Cards/RequireVariant/MaxRequire.hpp"
#include "Cards/RequireVariant/NoneRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
#include "EventSystem/EffectSystem.hpp"
#include <memory>

namespace Cards::Variant {
SmallShieldCard::SmallShieldCard()
    : Card(3, 1) {
    m_CardDescription = "Add [ ] shield";
    m_CardName = "SMALL SHIELD";
    m_Color = Cards::CardColor::ORANGE;
    AddRequireSlot(std::make_shared<RequireVariant::MaxRequire>(*this, 3));
}
void SmallShieldCard::Use(EventSystem::BattleSystem &currentBattle) const {
    if (!IsFit()) {
        return;
    }
    currentBattle.UseCard([this](EventSystem::BattleSystem &currentBattle) {
        switch (currentBattle.GetCurrentStatus()) {

        case EventSystem::BattleStatus::PLAYERTURN:
            currentBattle.ApplyEffect(
                currentBattle.GetPlayer().first,
                EventSystem::EffectSystem::BattleEffect::SHIELD,
                m_CardRequireSlot[0]->GetContainDiceNum());
            break;
        case EventSystem::BattleStatus::ENEMYTURN:
            currentBattle.ApplyEffect(
                currentBattle.GetEnemy().first,
                EventSystem::EffectSystem::BattleEffect::SHIELD,
                m_CardRequireSlot[0]->GetContainDiceNum());
            break;
        }
    });
    currentBattle.RemoveDice(m_CardRequireSlot[0]->GetContainDice());
    for (auto event : m_OnCardUsed) {
        event.second();
    }
}
} // namespace Cards::Variant
