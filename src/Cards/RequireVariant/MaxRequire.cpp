#include "Cards/RequireVariant/MaxRequire.hpp"
#include "DiceUtils/Dice.hpp"
#include "UI/CardsRenderer/RequireSlotRenderer.hpp"
#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include <memory>

namespace Cards::RequireVariant {

std::shared_ptr<UI::CardsRenderer::RequireSlotRenderer>
MaxRequire::GetRenderer() {
    auto renderer =
        std::make_shared<UI::CardsRenderer::RequireSlotRenderer>(*this);
    auto child = std::make_shared<Util::GameObject>();
    child->SetDrawable(std::make_shared<Util::Text>(
        RESOURCE_DIR "/NotoSans-Regular.ttf", 20,
        "Max\n    " + std::to_string(m_Max) + "   ",
        Util::Color(255, 255, 255)));
    renderer->AddChild(child);
    return renderer;
}
} // namespace Cards::RequireVariant
