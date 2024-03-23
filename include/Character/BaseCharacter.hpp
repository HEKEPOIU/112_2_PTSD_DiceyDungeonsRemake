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
    BaseCharacter(const std::string &name, int level, int maxHp, int currentHp,
                  const std::string &path);

    virtual void RoundStart(EventSystem::BattleSystem &currentBattle);
    virtual void RoundUpdate(EventSystem::BattleSystem &currentBattle);
    virtual void RoundEnd(EventSystem::BattleSystem &currentBattle);
    virtual void SetBattlePosition() = 0;
    Util::Transform &GetTransform() { return m_Transform; }
    void BindOnCurrentHealthChange(
        const std::string &eventId,
        std::function<void(int, int)> onCurrentHealthChange);
    void BindOnMaxHealthChange(const std::string &eventId,
                               std::function<void(int, int)> onMaxHealthChange);

    void UnBindOnCurrentHealthChange(const std::string &eventId);
    void UnBindOnMaxHealthChange(const std::string &eventId);
    const std::string &GetName() const { return m_Name; }

    int GetCurrentHealth() const { return m_HealthSystem->GetCurrentHealth(); }
    int GetMaxHealth() const { return m_HealthSystem->GetMaxHealth(); }

protected:
    std::string m_Name;
    std::shared_ptr<Util::Image> m_CharacterImage;
    std::unique_ptr<HealthSystem> m_HealthSystem;
    std::unique_ptr<Cards::CardSystem> m_BattleCards =
        std::make_unique<Cards::CardSystem>(3, 2);
    int m_Level;
};
} // namespace Character

#endif
