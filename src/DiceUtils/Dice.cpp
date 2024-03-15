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

glm::vec4 Dice::GetBoundingBox() const {
    glm::vec2 selfPos = m_Transform.translation;
    glm::vec2 selfSize = GetScaledSize();

    return {selfPos.x - selfSize.x / 2, selfPos.x + selfSize.x / 2,
            selfPos.y - selfSize.y / 2, selfPos.y + selfSize.y / 2};
}

bool Dice::IsOnTop(const glm::vec2 &position) const {
    auto dicebbox = GetBoundingBox();
    return (dicebbox.x < position.x && dicebbox.y > position.x &&
            dicebbox.z < position.y && dicebbox.w > position.y);
}

std::array<std::shared_ptr<Util::Image>, 6> Dice::image{};
} // namespace DiceUtils
