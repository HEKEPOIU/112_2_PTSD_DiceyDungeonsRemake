#ifndef DICEUTIllS_DICE_HPP
#define DICEUTIllS_DICE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <array>
#include <glm/fwd.hpp>
#include <memory>

namespace DiceUtils {
class Dice : public Util::GameObject {
public:
    enum class DiceStates { NORMAL, FIRE, LOCK };

    Dice(unsigned short diceNum);

    void SetPosition(const glm::vec2 &pos) { m_Transform.translation = pos; };
    void SetNum(unsigned short diceNum);
    unsigned short GetNum() const { return m_DiceNumber; };
    void SetCurrentState(DiceStates value) { currentState = value; };
    DiceStates GetCurrentState() { return currentState; }
    bool IsOnTop(const glm::vec2 &position) const;
    glm::vec4 GetBoundingBox() const;

private:
    void InitImage();
    static std::array<std::shared_ptr<Util::Image>, 6> image;
    unsigned short m_DiceNumber;
    DiceStates currentState = DiceStates::NORMAL;
};

} // namespace DiceUtils

#endif
