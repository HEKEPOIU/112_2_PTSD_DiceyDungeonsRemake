#ifndef CARDS_CARDREGISTER_HPP
#define CARDS_CARDREGISTER_HPP

#include "Cards/CardFactory.hpp"
#include "Cards/Variant/BattleAxeCard.hpp"
#include "Cards/Variant/BroadSwordCard.hpp"
#include "Cards/Variant/BucklerCard.hpp"
#include "Cards/Variant/BumpCard.hpp"
#include "Cards/Variant/CombatRollSkill.hpp"
#include "Cards/Variant/CrystalSwordCard.hpp"
#include "Cards/Variant/DaggerCard.hpp"
#include "Cards/Variant/FirstAidKitCard.hpp"
#include "Cards/Variant/HealingCrystalCard.hpp"
#include "Cards/Variant/IronShieldCard.hpp"
#include "Cards/Variant/JugglingBallCard.hpp"
#include "Cards/Variant/MagicMissileCard.hpp"
#include "Cards/Variant/MagicShieldCard.hpp"
#include "Cards/Variant/PeaShooterCard.hpp"
#include "Cards/Variant/PirateHookCard.hpp"
#include "Cards/Variant/SixShooterCard.hpp"
#include "Cards/Variant/SmallShieldCard.hpp"
#include "Cards/Variant/SnakeEyeChard.hpp"
#include "Cards/Variant/SpatulaCard.hpp"
#include "Cards/Variant/SpikedShieldCard.hpp"
#include "Cards/Variant/SwordCard.hpp"
#include "Cards/Variant/TargetShieldCard.hpp"
#include <memory>
namespace Cards {
class CardRegister {
public:
    CardRegister() {
        // Register card, should it put in constructor?
        CardFactory::RegisterCard(
            -1, [] { return std::make_shared<Variant::CombatRollSkill>(); });

        CardFactory::RegisterCard(
            1, [] { return std::make_shared<Variant::SwordCard>(); });

        CardFactory::RegisterCard(
            2, [] { return std::make_shared<Variant::BroadSwordCard>(); });
        CardFactory::RegisterCard(
            3, [] { return std::make_shared<Variant::SmallShieldCard>(); });
        CardFactory::RegisterCard(
            4, [] { return std::make_shared<Variant::SpikedShieldCard>(); });
        CardFactory::RegisterCard(
            5, [] { return std::make_shared<Variant::BattleAxeCard>(); });
        CardFactory::RegisterCard(
            6, [] { return std::make_shared<Variant::SixShooterCard>(); });
        CardFactory::RegisterCard(
            7, [] { return std::make_shared<Variant::CrystalSwordCard>(); });
        CardFactory::RegisterCard(
            8, [] { return std::make_shared<Variant::PeaShooterCard>(); });
        CardFactory::RegisterCard(
            9, [] { return std::make_shared<Variant::DaggerCard>(); });
        CardFactory::RegisterCard(
            10, [] { return std::make_shared<Variant::JugglingBallCard>(); });
        CardFactory::RegisterCard(
            11, [] { return std::make_shared<Variant::IronShieldCard>(); });
        CardFactory::RegisterCard(
            12, [] { return std::make_shared<Variant::TargetShieldCard>(); });
        CardFactory::RegisterCard(
            13, [] { return std::make_shared<Variant::BucklerCard>(); });
        CardFactory::RegisterCard(
            14, [] { return std::make_shared<Variant::BumpCard>(); });
        CardFactory::RegisterCard(
            15, [] { return std::make_shared<Variant::SpatulaCard>(); });
        CardFactory::RegisterCard(
            16, [] { return std::make_shared<Variant::SnakeEyeChard>(); });
        CardFactory::RegisterCard(
            17, [] { return std::make_shared<Variant::HealingCrystalCard>(); });
        CardFactory::RegisterCard(
            18, [] { return std::make_shared<Variant::FirstAidKitCard>(); });
        CardFactory::RegisterCard(
            19, [] { return std::make_shared<Variant::MagicMissileCard>(); });
        CardFactory::RegisterCard(
            20, [] { return std::make_shared<Variant::MagicShieldCard>(); });
        CardFactory::RegisterCard(
            21, [] { return std::make_shared<Variant::PirateHookCard>(); });
    }
};
} // namespace Cards

#endif
