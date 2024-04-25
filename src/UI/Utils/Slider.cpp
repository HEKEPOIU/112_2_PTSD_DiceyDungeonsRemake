#include "UI/Utils/Slider.hpp"
#include "Util/GameObject.hpp"
#include "Util/SpriteSheet.hpp"
#include <glm/common.hpp>
#include <memory>

namespace UI::Utils {

Slider::Slider(const std::string &baseImagePath,
               const std::string &fillImagePath, int currentValue, int minValue,
               int maxValue, int zIndex)
    : m_FillImageSpriteSheet(
          std::make_shared<Util::SpriteSheet>(fillImagePath)),
      m_BaseImageSpriteSheet(
          std::make_shared<Util::SpriteSheet>(baseImagePath)),
      m_CurrentValue(currentValue),
      m_MinValue(minValue),
      m_MaxValue(maxValue) {

    SetZIndex(zIndex);
    SetDrawable(m_BaseImageSpriteSheet);
    fillObject = std::make_shared<Util::GameObject>();
    fillObject->SetDrawable(m_FillImageSpriteSheet);
    auto childText = std::make_shared<Util::GameObject>();
    m_sliderValue = std::make_shared<Util::Text>(
        RESOURCE_DIR "/NotoSans-Regular.ttf", 50,
        std::to_string(currentValue) + " / " + std::to_string(maxValue),
        Util::Color(255, 255, 255));
    childText->SetDrawable(m_sliderValue);

    // this is weird, if i don't set the z index, the childFill will disappear,
    // wtf?
    childText->SetZIndex(GetZIndex() + 2);
    fillObject->SetZIndex(GetZIndex() + 1);
    m_SliderPos = m_Transform.translation;
    // LOG_ERROR("zindex of childFill is {}", childFill->GetZIndex());
    AddChild(fillObject);
    AddChild(childText);
}

void Slider::SetCurrentValue(int value) {
    m_CurrentValue = glm::min(glm::max(value, m_MinValue), m_MaxValue);
    m_sliderValue->SetText(std::to_string(m_CurrentValue) + " / " +
                           std::to_string(m_MaxValue));

    auto currentDrawRect = m_FillImageSpriteSheet->GetCurrentDrawRect();
    auto newFillPos = fillObject->m_Transform.translation;

    // TODO: something weird
    int fillWidth = (float)(m_CurrentValue - m_MinValue) /
                    (m_MaxValue - m_MinValue) * m_MaxFillRect.h;

    newFillPos.x = (m_SliderPos.x - (m_MaxFillRect.h - fillWidth) / 4.);

    currentDrawRect.h = fillWidth;
    fillObject->m_Transform.translation = newFillPos;
    m_FillImageSpriteSheet->SetDrawRect(currentDrawRect);
}

void Slider::SetMaxValue(int value) {
    m_MaxValue = value;
    SetCurrentValue(m_CurrentValue);
}

void Slider::SetMinValue(int value) {
    m_MinValue = value;
    SetCurrentValue(m_CurrentValue);
}

} // namespace UI::Utils
