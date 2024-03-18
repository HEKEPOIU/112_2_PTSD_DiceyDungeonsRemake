#include "UI/UIManager.hpp"
#include "Util/Image.hpp"
#include <memory>

namespace UI {
UIManager::UIManager()
    : Util::GameObject() {
    // TODO: This should be dependency injected base on context.
    SetDrawable(std::make_shared<Util::Image>(
        RESOURCE_DIR "/graphics/backgrounds/combat/castle/static_1080.png"));
}
} // namespace UI
