#ifndef CHARACTER_BASECHARACTER_HPP
#define CHARACTER_BASECHARACTER_HPP

#include "Cards/CardSystem.hpp"
#include "Character/HealthSystem.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <memory>
#include <string>

namespace EventSystem {
class BattleSystem; // 前向声明
}
namespace Character {
class BaseCharacter : public Util::GameObject {

public:
    BaseCharacter(int level, int maxHp, int currentHp, const std::string &path);

    virtual void RoundStart(EventSystem::BattleSystem &currentBattle) = 0;
    virtual void RoundUpdate(EventSystem::BattleSystem &currentBattle) = 0;
    virtual void RoundEnd(EventSystem::BattleSystem &currentBattle) = 0;
    virtual void SetBattlePosition() = 0;
    Util::Transform &GetTransform() { return m_Transform; }

protected:
    std::shared_ptr<Util::Image> m_CharacterImage;
    std::unique_ptr<HealthSystem> m_HealthSystem;
    std::unique_ptr<Cards::CardSystem> m_BattleCards =
        std::make_unique<Cards::CardSystem>(3, 2);
    int m_Level;
};
} // namespace Character

#endif
