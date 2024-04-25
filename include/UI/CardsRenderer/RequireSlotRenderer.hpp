#ifndef UI_CARDSRENDERER_REQUIRESLOTRENDERER_HPP
#define UI_CARDSRENDERER_REQUIRESLOTRENDERER_HPP

#include "Cards/Card.hpp"
#include "Cards/CardRequireSlot.hpp"
#include "DiceUtils/Dice.hpp"
#include "Util/GameObject.hpp"
#include "Util/SpriteSheet.hpp"
#include <memory>

namespace Cards {
class CardRequireSlot;
}

namespace UI::CardsRenderer {
class RequireSlotRenderer : public Util::GameObject {

public:
    RequireSlotRenderer(Cards::CardRequireSlot &requireSlot);
    void Use(const std::shared_ptr<DiceUtils::Dice> &dice,
             EventSystem::BattleSystem &currentBattle) {
        if (IsFit(dice)) {
            m_RequireSlot.SetContainDice(dice, currentBattle);
        }
    }

    bool IsFit(const std::shared_ptr<DiceUtils::Dice> &dice) {
        return m_RequireSlot.IsFit(dice->GetNum());
    }
    void Reset() { m_RequireSlot.Reset(); }

private:
    void InitRenderer();
    Cards::CardRequireSlot &m_RequireSlot;
    static std::shared_ptr<Util::SpriteSheet> renderer;
};
} // namespace UI::CardsRenderer

#endif
