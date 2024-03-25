#include "DiceUtils/Dice.hpp"
#include "Util/Image.hpp"
#include <glm/fwd.hpp>
#include <memory>
#include <stdexcept>

namespace DiceUtils {

Dice::Dice(unsigned short diceNum)
    : m_DiceNumber(diceNum) {
    SetNum(diceNum);
    m_Transform.scale = {.6, .6};
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
        std::make_shared<Util::Image>(RESOURCE_DIR "/RollDice/Dice_1.png"),
        std::make_shared<Util::Image>(RESOURCE_DIR "/RollDice/Dice_2.png"),
        std::make_shared<Util::Image>(RESOURCE_DIR "/RollDice/Dice_3.png"),
        std::make_shared<Util::Image>(RESOURCE_DIR "/RollDice/Dice_4.png"),
        std::make_shared<Util::Image>(RESOURCE_DIR "/RollDice/Dice_5.png"),
        std::make_shared<Util::Image>(RESOURCE_DIR "/RollDice/Dice_6.png")};
}
std::array<std::shared_ptr<Util::Image>, 6> Dice::image{};
} // namespace DiceUtils
