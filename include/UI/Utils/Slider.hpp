#ifndef UI_UTILS_SLIDER_HPP
#define UI_UTILS_SLIDER_HPP

#include "SDL_rect.h"
#include "Util/GameObject.hpp"
#include "Util/SpriteSheet.hpp"
#include "Util/Text.hpp"
#include <memory>
#include <string>
namespace UI::Utils {

class Slider : public Util::GameObject {
public:
    Slider(const std::string &baseImagePath, const std::string &fillImagePath,
           int currentValue, int minValue, int maxValue);

    const std::shared_ptr<Util::SpriteSheet> GetFillImageSpriteSheet() const {
        return m_FillImageSpriteSheet;
    }
    const std::shared_ptr<Util::SpriteSheet> GetBaseImageSpriteSheet() const {
        return m_BaseImageSpriteSheet;
    }

private:
    std::shared_ptr<Util::SpriteSheet> m_FillImageSpriteSheet;
    std::shared_ptr<Util::SpriteSheet> m_BaseImageSpriteSheet;
    std::shared_ptr<Util::Text> m_sliderValue;
    int m_CurrentValue;
    int m_MinValue;
    int m_MaxValue;
};
} // namespace UI::Utils

#endif
