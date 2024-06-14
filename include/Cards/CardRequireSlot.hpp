#ifndef CARDS_CARDREQUIRESLOT_HPP
#define CARDS_CARDREQUIRESLOT_HPP

#include "Cards/Card.hpp"
#include "DiceUtils/Dice.hpp"

#include <memory>
namespace UI::CardsRenderer {
class RequireSlotRenderer;
}

namespace Cards {
class CardRequireSlot {
public:
    CardRequireSlot(Card &card)
        : m_Owner(card){};

    virtual bool IsFit(int size) = 0;
    virtual void SetContainDice(const std::shared_ptr<DiceUtils::Dice> &dice,
                                EventSystem::BattleSystem &currentBattle) {
        if (m_ContainDice == dice) {
            return;
        }
        m_ContainDice = dice;
        m_Owner.Use(currentBattle);
    }

    virtual void Reset() { m_ContainDice = nullptr; }

    int GetContainDiceNum() const { return m_ContainDice->GetNum(); }
    const std::shared_ptr<DiceUtils::Dice> &GetContainDice() {
        return m_ContainDice;
    }

    virtual std::shared_ptr<UI::CardsRenderer::RequireSlotRenderer>
    GetRenderer() = 0;

protected:
    std::shared_ptr<DiceUtils::Dice> m_ContainDice;
    Card &m_Owner;
};
} // namespace Cards

#endif
