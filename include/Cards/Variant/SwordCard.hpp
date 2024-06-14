#ifndef CARDS_VARIANT_SWORDCARD_HPP
#define CARDS_VARIANT_SWORDCARD_HPP

#include "Cards/Card.hpp"
namespace Cards::Variant {
class SwordCard : public Cards::Card {
public:
    SwordCard();
    virtual void Use(EventSystem::BattleSystem &currentBattle) override;
};
} // namespace Cards::Variant

#endif
