#include "Cards/Variant/SmallShieldCard.hpp"
#include "Cards/Card.hpp"
#include "Cards/RequireVariant/MaxRequire.hpp"
#include "Cards/RequireVariant/NoneRequire.hpp"
#include "EventSystem/BattleSystem.hpp"
#include <memory>

namespace Cards::Variant {
SmallShieldCard::SmallShieldCard()
    : Card(3, 1) {
    m_CardDescription = "Add [ ] shield";
    m_CardName = "SMALL SHIELD";
    m_Color = Cards::CardColor::ORANGE;
    AddRequireSlot(std::make_shared<RequireVariant::MaxRequire>(*this, 3));
}
void SmallShieldCard::Use(EventSystem::BattleSystem &currentBattle) const {}
} // namespace Cards::Variant
