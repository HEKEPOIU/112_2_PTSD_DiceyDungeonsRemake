#ifndef CARDS_VARIANT_SWORDCARD_HPP
#define CARDS_VARIANT_SWORDCARD_HPP

#include "Cards/Card.hpp"
namespace Cards::Variant {
class SwordCard : public Cards::Card {
public:
    SwordCard(int id, int size);
    virtual void Use(const std::shared_ptr<EventSystem::BattleSystem>
                         &currentBattle) const override;
};
} // namespace Cards::Variant

#endif
