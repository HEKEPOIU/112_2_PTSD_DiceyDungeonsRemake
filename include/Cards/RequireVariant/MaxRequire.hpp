#ifndef CARDS_REQUIREVARIANT_MAXREQUIRE_HPP
#define CARDS_REQUIREVARIANT_MAXREQUIRE_HPP

#include "Cards/CardRequireSlot.hpp"
namespace Cards::RequireVariant {
class MaxRequire : public CardRequireSlot {
public:
    MaxRequire(Card &card, int num)
        : CardRequireSlot(card),
          m_Max(num) {}
    virtual bool IsFit(int size) override { return size <= m_Max; };
    virtual std::shared_ptr<UI::CardsRenderer::RequireSlotRenderer>
    GetRenderer() override;

private:
    int m_Max;
};
} // namespace Cards::RequireVariant

#endif
