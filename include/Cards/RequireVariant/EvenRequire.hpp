
#ifndef CARDS_REQUIREVARIANT_EvenRequire_HPP
#define CARDS_REQUIREVARIANT_EvenRequire_HPP

#include "Cards/CardRequireSlot.hpp"
#include "UI/CardsRenderer/RequireSlotRenderer.hpp"
#include "Util/Text.hpp"
namespace Cards::RequireVariant {
class EvenRequire : public CardRequireSlot {
public:
    EvenRequire(Card &card)
        : CardRequireSlot(card) {}
    virtual bool IsFit(int size) override { return (size % 2) == 0; };
    virtual std::shared_ptr<UI::CardsRenderer::RequireSlotRenderer>
    GetRenderer() override {
        auto renderer =
            std::make_shared<UI::CardsRenderer::RequireSlotRenderer>(*this);
        auto child = std::make_shared<Util::GameObject>();
        child->SetDrawable(std::make_shared<Util::Text>(
            RESOURCE_DIR "/NotoSans-Regular.ttf", 20, "EVEN",
            Util::Color(255, 255, 255)));
        renderer->AddChild(child);
        return renderer;
    };
};
} // namespace Cards::RequireVariant

#endif
