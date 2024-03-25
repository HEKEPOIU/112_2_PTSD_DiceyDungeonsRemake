#ifndef UI_UTILS_SLIDER_HPP
#define UI_UTILS_SLIDER_HPP

#include "SDL_rect.h"
#include "Util/GameObject.hpp"
#include "Util/SpriteSheet.hpp"
#include "Util/Text.hpp"
#include "Util/Transform.hpp"
#include <glm/fwd.hpp>
#include <memory>
#include <string>
namespace UI::Utils {

class Slider : public Util::GameObject {
    // TODO: ADD Slider direction enum.

public:
    Slider(const std::string &baseImagePath, const std::string &fillImagePath,
           int currentValue, int minValue, int maxValue, int zIndex);

    const std::shared_ptr<Util::SpriteSheet> GetFillImageSpriteSheet() const {
        return m_FillImageSpriteSheet;
    }
    const std::shared_ptr<Util::SpriteSheet> GetBaseImageSpriteSheet() const {
        return m_BaseImageSpriteSheet;
    }

    void SetCurrentValue(int value);
    void SetMaxValue(int value);
    void SetMinValue(int value);
    void SetFillImageSpriteSheet(const SDL_Rect &rect) {
        m_FillImageSpriteSheet->SetDrawRect(rect);
        m_MaxFillRect = rect;
    }
    void SetBaseImageSpriteSheet(const SDL_Rect &rect) {
        m_BaseImageSpriteSheet->SetDrawRect(rect);
    }

    void SetPostion(const glm::vec2 &pos) {
        m_Transform.translation = pos;
        for (auto child : m_Children) {
            child->m_Transform.translation = pos;
        }
        m_SliderPos = pos;
    }
    void SetScale(const glm::vec2 &scale) {
        m_Transform.scale = scale;
        for (auto child : m_Children) {
            child->m_Transform.scale = scale;
        }
    }

    const std::shared_ptr<Util::GameObject> &GetFillObject() {
        return fillObject;
    }

private:
    std::shared_ptr<Util::SpriteSheet> m_FillImageSpriteSheet;
    std::shared_ptr<Util::SpriteSheet> m_BaseImageSpriteSheet;
    std::shared_ptr<Util::GameObject> fillObject;
    std::shared_ptr<Util::Text> m_sliderValue;
    SDL_Rect m_MaxFillRect;
    glm::vec2 m_SliderPos;
    int m_CurrentValue;
    int m_MinValue;
    int m_MaxValue;
};
} // namespace UI::Utils

#endif
