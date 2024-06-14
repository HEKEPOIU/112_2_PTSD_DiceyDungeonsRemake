#ifndef CARDS_REQUIREVARIANT_TotalRequire_HPP
#define CARDS_REQUIREVARIANT_TotalRequire_HPP

#include "Cards/CardRequireSlot.hpp"
#include "UI/CardsRenderer/RequireSlotRenderer.hpp"
#include "Util/Text.hpp"
#include <string>
namespace Cards::RequireVariant {
class TotalRequire : public CardRequireSlot {
public:
    TotalRequire(Card &card, int num)
        : CardRequireSlot(card),
          m_Max(num) {}
    virtual bool IsFit(int size) override { return true; };
    virtual std::shared_ptr<UI::CardsRenderer::RequireSlotRenderer>
    GetRenderer() override {
        auto renderer =
            std::make_shared<UI::CardsRenderer::RequireSlotRenderer>(*this);
        auto child = std::make_shared<Util::GameObject>();
        child->SetDrawable(std::make_shared<Util::Text>(
            RESOURCE_DIR "/NotoSans-Regular.ttf", 20,
            std::to_string(m_Max - m_Current), Util::Color(255, 255, 255)));
        renderer->AddChild(child);
        return renderer;
    };

private:
    int m_Max;
    int m_Current = 0;
};
} // namespace Cards::RequireVariant

#endif
