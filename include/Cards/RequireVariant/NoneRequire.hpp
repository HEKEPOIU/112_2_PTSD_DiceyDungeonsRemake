#ifndef CARDS_REQUIREVARIANT_NONEREQUIRE_HPP
#define CARDS_REQUIREVARIANT_NONEREQUIRE_HPP

#include "Cards/CardRequireSlot.hpp"
namespace Cards::RequireVariant {
class NoneRequire : public CardRequireSlot {
public:
    NoneRequire(Card &card)
        : CardRequireSlot(card) {}
    virtual bool IsFit(int size) override { return true; };
    virtual std::shared_ptr<UI::CardsRenderer::RequireSlotRenderer>
    GetRenderer() override;
};
} // namespace Cards::RequireVariant

#endif
