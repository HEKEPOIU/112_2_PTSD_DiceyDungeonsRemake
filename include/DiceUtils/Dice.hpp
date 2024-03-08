#ifndef DICEUTIllS_DICE_HPP
#define DICEUTIllS_DICE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <array>
#include <memory>

namespace DiceUtils {
class Dice : public Util::GameObject {
public:
    Dice(unsigned short diceNum);

private:
    void InitImage();
    static std::array<std::shared_ptr<Util::Image>, 6> image;
    unsigned short m_DiceNumber;
};

} // namespace DiceUtils

#endif
