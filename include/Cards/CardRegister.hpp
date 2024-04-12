#ifndef CARDS_CARDREGISTER_HPP
#define CARDS_CARDREGISTER_HPP

#include "Cards/CardFactory.hpp"
#include "Cards/Variant/BroadSwordCard.hpp"
#include "Cards/Variant/SmallShieldCard.hpp"
#include "Cards/Variant/SwordCard.hpp"
#include <memory>
namespace Cards {
class CardRegister {
public:
    CardRegister() {
        // Register card, should it put in constructor?
        CardFactory::RegisterCard(
            1, [] { return std::make_shared<Variant::SwordCard>(); });

        CardFactory::RegisterCard(
            2, [] { return std::make_shared<Variant::BroadSwordCard>(); });
        CardFactory::RegisterCard(
            3, [] { return std::make_shared<Variant::SmallShieldCard>(); });
    }
};
} // namespace Cards

#endif
