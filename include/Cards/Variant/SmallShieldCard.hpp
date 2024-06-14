#ifndef CARDS_VARIANT_SMALLSHIELDCARD_HPP
#define CARDS_VARIANT_SMALLSHIELDCARD_HPP

#include "Cards/Card.hpp"
namespace Cards::Variant {
class SmallShieldCard : public Cards::Card {
public:
    SmallShieldCard();
    virtual void Use(EventSystem::BattleSystem &currentBattle) override;
};
} // namespace Cards::Variant

#endif
