#include "Cards/Variant/SwordCard.hpp"
#include "Cards/Card.hpp"
#include "Cards/RequireVariant/NoneRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
#include <memory>

namespace Cards::Variant {
SwordCard::SwordCard(int id, int size)
    : Card(id, size) {
    m_CardDescription = "Do [ ] damage";
    m_CardName = "SWORD";
    m_Color = Cards::CardColor::RED;
    AddRequireSlot(std::make_shared<RequireVariant::NoneRequire>(*this));
    AddRequireSlot(std::make_shared<RequireVariant::NoneRequire>(*this));
}
void SwordCard::Use(
    const std::shared_ptr<EventSystem::BattleSystem> &currentBattle) const {
    switch (currentBattle->GetCurrentStatus()) {

    case EventSystem::BattleSystem::CurrentStatus::PLAYERTURN:
        currentBattle->GetEnemy().first->ModifyCurrentHealth(
            -(m_CardRequireSlot[0]->GetContainDiceNum()));
        break;
    case EventSystem::BattleSystem::CurrentStatus::ENEMYTURN:
        currentBattle->GetPlayer().first->ModifyCurrentHealth(
            -(m_CardRequireSlot[0]->GetContainDiceNum()));
        break;
    }
}
} // namespace Cards::Variant
