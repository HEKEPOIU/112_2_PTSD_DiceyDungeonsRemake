#include "Cards/RequireVariant/NoneRequire.hpp"
#include "UI/CardsRenderer/RequireSlotRenderer.hpp"
#include <memory>

namespace Cards::RequireVariant {
std::shared_ptr<UI::CardsRenderer::RequireSlotRenderer>
NoneRequire::GetRenderer() {
    auto renderer =
        std::make_shared<UI::CardsRenderer::RequireSlotRenderer>(*this);
    return renderer;
}
} // namespace Cards::RequireVariant
