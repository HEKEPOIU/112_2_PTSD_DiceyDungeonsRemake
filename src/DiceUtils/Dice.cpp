#include "DiceUtils/Dice.hpp"
#include "Util/SpriteSheet.hpp"
#include <glm/fwd.hpp>
#include <memory>
#include <stdexcept>

namespace DiceUtils {

Dice::Dice(unsigned short diceNum)
    : m_DiceNumber(diceNum) {
    SetNum(diceNum);
    m_Transform.scale = {.5, .5};
}

void Dice::SetNum(unsigned short diceNum) {
    if (diceNum > 6 || diceNum < 1) {
        throw std::invalid_argument("Dice Only have 6 face");
        return;
    }

    if (image[0] == nullptr) {
        InitImage();
    }
    SetDrawable(image[diceNum - 1]);
}

void Dice::InitImage() {
    image = {
        std::make_shared<Util::SpriteSheet>(RESOURCE_DIR "/graphics/pack1.png"),
        std::make_shared<Util::SpriteSheet>(RESOURCE_DIR "/graphics/pack1.png"),
        std::make_shared<Util::SpriteSheet>(RESOURCE_DIR "/graphics/pack1.png"),
        std::make_shared<Util::SpriteSheet>(RESOURCE_DIR "/graphics/pack1.png"),
        std::make_shared<Util::SpriteSheet>(RESOURCE_DIR "/graphics/pack1.png"),
        std::make_shared<Util::SpriteSheet>(RESOURCE_DIR
                                            "/graphics/pack1.png")};
    image[0]->SetDrawRect({894, 945, 249, 249});
    image[1]->SetDrawRect({291, 1145, 249, 249});
    image[2]->SetDrawRect({540, 1194, 249, 249});
    image[3]->SetDrawRect({789, 1194, 249, 249});
    image[4]->SetDrawRect({319, 1618, 249, 249});
    image[5]->SetDrawRect({569, 1603, 249, 249});
}
std::array<std::shared_ptr<Util::SpriteSheet>, 6> Dice::image{};
} // namespace DiceUtils
