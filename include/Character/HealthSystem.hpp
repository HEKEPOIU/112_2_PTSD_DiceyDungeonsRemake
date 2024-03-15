#ifndef CHARACTER_HEALTHSYSTEM_HPP
#define CHARACTER_HEALTHSYSTEM_HPP

#include <functional>
namespace Character {
class HealthSystem {

public:
    HealthSystem(int maxHp, int currentHp);

    int GetCurrentHealth() const { return m_CurrentHealth; }
    int GetMaxHealth() const { return m_MaxHealth; }
    void SetCurrentHealth(int value);
    void SetMaxHealth(int value);
    void ModifyCurrentHealth(int addValue);
    void ModifyMaxHealth(int addValue);

private:
    std::function<void(int, int)> m_OnCurrentHealthChange;
    std::function<void(int, int)> m_OnMaxHealthChange;
    int m_MaxHealth;
    int m_CurrentHealth;
};
} // namespace Character

#endif
