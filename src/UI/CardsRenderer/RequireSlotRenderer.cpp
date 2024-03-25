#include "UI/CardsRenderer/RequireSlotRenderer.hpp"

namespace UI::CardsRenderer {
RequireSlotRenderer::RequireSlotRenderer(Cards::CardRequireSlot &requireSlot)
    : m_RequireSlot(requireSlot) {
    if (renderer == nullptr) {
        InitRenderer();
    }
    SetDrawable(renderer);
}

void RequireSlotRenderer::InitRenderer() {
    renderer =
        std::make_shared<Util::SpriteSheet>(RESOURCE_DIR "/graphics/pack1.png");
    renderer->SetDrawRect({1316, 1693, 244, 245});
}
std::shared_ptr<Util::SpriteSheet> RequireSlotRenderer::renderer = nullptr;
} // namespace UI::CardsRenderer
