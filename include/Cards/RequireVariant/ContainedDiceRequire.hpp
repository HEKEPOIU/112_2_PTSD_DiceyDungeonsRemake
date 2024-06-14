#ifndef CARDS_REQUIREVARIANT_CONTAINEDDICEREQUIRE_HPP
#define CARDS_REQUIREVARIANT_CONTAINEDDICEREQUIRE_HPP

#include "Cards/CardRequireSlot.hpp"
namespace Cards::RequireVariant {
class ContainedDiceRequire : public CardRequireSlot {
public:
    ContainedDiceRequire(Card &card, int num)
        : CardRequireSlot(card) {
        m_ContainDice = std::make_shared<DiceUtils::Dice>(num);
    }
    virtual bool IsFit(int size) override { return true; };
    virtual void
    SetContainDice(const std::shared_ptr<DiceUtils::Dice> &dice,
                   EventSystem::BattleSystem &currentBattle) override {
        m_Owner.Use(currentBattle);
    };

    virtual void Reset() override { /*Just don't do anything*/ }
    virtual std::shared_ptr<UI::CardsRenderer::RequireSlotRenderer>
    GetRenderer() override;
};
} // namespace Cards::RequireVariant
#endif
