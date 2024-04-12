#include "Cards/RequireVariant/ContainedDiceRequire.hpp"
#include "DiceUtils/Dice.hpp"
#include "UI/CardsRenderer/RequireSlotRenderer.hpp"
#include <memory>

namespace Cards::RequireVariant {
std::shared_ptr<UI::CardsRenderer::RequireSlotRenderer>
ContainedDiceRequire::GetRenderer() {
    auto renderer =
        std::make_shared<UI::CardsRenderer::RequireSlotRenderer>(*this);
    auto childDice = std::make_shared<DiceUtils::Dice>(m_ContainDice->GetNum());
    renderer->AddChild(childDice);
    return renderer;
}
} // namespace Cards::RequireVariant
