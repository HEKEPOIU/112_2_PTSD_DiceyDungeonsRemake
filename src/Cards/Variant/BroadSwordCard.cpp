#include "Cards/Variant/BroadSwordCard.hpp"
#include "Cards/Card.hpp"
#include "Cards/RequireVariant/ContainedDiceRequire.hpp"
#include "Cards/RequireVariant/NoneRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
#include <memory>

namespace Cards::Variant {
BroadSwordCard::BroadSwordCard()
    : Card(2, 2) {
    m_CardDescription = "Do [ ] + 2 damage";
    m_CardName = "Broadsword";
    m_Color = Cards::CardColor::RED;
    AddRequireSlot(std::make_shared<RequireVariant::NoneRequire>(*this));
    AddRequireSlot(
        std::make_shared<RequireVariant::ContainedDiceRequire>(*this, 2));
}
void BroadSwordCard::Use(EventSystem::BattleSystem &currentBattle) const {
    if (!IsFit()) {
        return;
    }
    currentBattle.UseCard([this](EventSystem::BattleSystem &currentBattle) {
        switch (currentBattle.GetCurrentStatus()) {

        case EventSystem::BattleStatus::PLAYERTURN:
            currentBattle.ApplyDamage(
                currentBattle.GetEnemy().first,
                (m_CardRequireSlot[0]->GetContainDiceNum() +
                 m_CardRequireSlot[1]->GetContainDiceNum()));
            break;
        case EventSystem::BattleStatus::ENEMYTURN:
            currentBattle.ApplyDamage(
                currentBattle.GetPlayer().first,
                (m_CardRequireSlot[0]->GetContainDiceNum() +
                 m_CardRequireSlot[1]->GetContainDiceNum()));
            break;
        }
    });
    currentBattle.RemoveDice(m_CardRequireSlot[0]->GetContainDice());
    for (auto event : m_OnCardUsed) {
        event.second();
    }
}
} // namespace Cards::Variant
