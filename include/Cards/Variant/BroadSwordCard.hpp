#ifndef CARDS_VARIANT_BROADSWORDCARD_HPP
#define CARDS_VARIANT_BROADSWORDCARD_HPP

#include "Cards/Card.hpp"
namespace Cards::Variant {
class BroadSwordCard : public Cards::Card {
public:
    BroadSwordCard();
    virtual void Use(EventSystem::BattleSystem &currentBattle) override;
};
} // namespace Cards::Variant

#endif
