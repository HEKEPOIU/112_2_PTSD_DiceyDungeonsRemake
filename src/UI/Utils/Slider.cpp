#include "UI/Utils/Slider.hpp"
#include "Util/GameObject.hpp"
#include "Util/SpriteSheet.hpp"
#include <memory>

namespace UI::Utils {

Slider::Slider(const std::string &baseImagePath,
               const std::string &fillImagePath, int currentValue, int minValue,
               int maxValue)
    : m_FillImageSpriteSheet(
          std::make_shared<Util::SpriteSheet>(fillImagePath)),
      m_BaseImageSpriteSheet(
          std::make_shared<Util::SpriteSheet>(baseImagePath)),
      m_CurrentValue(currentValue),
      m_MinValue(minValue),
      m_MaxValue(maxValue) {

    SetDrawable(m_BaseImageSpriteSheet);
    auto childFill = std::make_shared<Util::GameObject>();
    childFill->SetDrawable(m_FillImageSpriteSheet);
    auto childText = std::make_shared<Util::GameObject>();
    m_sliderValue = std::make_shared<Util::Text>(
        RESOURCE_DIR "/NotoSans-Regular.ttf", 35,
        std::to_string(currentValue) + " / " + std::to_string(maxValue),
        Util::Color(255, 255, 255));
    childText->SetDrawable(m_sliderValue);
    AddChild(childFill);
    AddChild(childText);
}
} // namespace UI::Utils
