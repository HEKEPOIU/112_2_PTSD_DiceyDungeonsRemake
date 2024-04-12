#include "Cards/Variant/SwordCard.hpp"
#include "Cards/Card.hpp"
#include "Cards/RequireVariant/NoneRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
#include <memory>

namespace Cards::Variant {
SwordCard::SwordCard()
    : Card(1, 2) {
    m_CardDescription = "Do [ ] damage";
    m_CardName = "SWORD";
    m_Color = Cards::CardColor::RED;
    AddRequireSlot(std::make_shared<RequireVariant::NoneRequire>(*this));
}
void SwordCard::Use(EventSystem::BattleSystem &currentBattle) const {
    Card::Use(currentBattle);

    // I Think this weird.
    currentBattle.UseCard([this](EventSystem::BattleSystem &currentBattle) {
        switch (currentBattle.GetCurrentStatus()) {

        case EventSystem::BattleStatus::PLAYERTURN:
            currentBattle.ApplyDamage(
                currentBattle.GetEnemy().first,
                (m_CardRequireSlot[0]->GetContainDiceNum()));
            break;
        case EventSystem::BattleStatus::ENEMYTURN:
            currentBattle.ApplyDamage(
                currentBattle.GetPlayer().first,
                (m_CardRequireSlot[0]->GetContainDiceNum()));
            break;
        }
    });
    currentBattle.RemoveDice(m_CardRequireSlot[0]->GetContainDice());
    for (auto event : m_OnCardUsed) {
        event.second();
    }
    // event On Card Used.
}
} // namespace Cards::Variant
