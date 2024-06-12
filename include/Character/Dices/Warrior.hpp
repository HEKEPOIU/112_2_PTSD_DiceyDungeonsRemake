#ifndef CHARACTER_DICES_THIEF_HPP
#define CHARACTER_DICES_THIEF_HPP

#include "Character/PlayerDice.hpp"
#include <string>

namespace Character {
namespace Dices {
class Warrior : public PlayerDice {
public:
    Warrior(const std::string &name, int level, int maxHp, int currentHp,
            const std::string &path, const std::string &levelImagePath);
    virtual void RoundStart(EventSystem::BattleSystem &currentBattle) override;

private:
    static constexpr std::array<int, 6> m_DicesPerLevel{2, 3, 3, 4, 4, 5};
};
} // namespace Dices
} // namespace Character

#endif
