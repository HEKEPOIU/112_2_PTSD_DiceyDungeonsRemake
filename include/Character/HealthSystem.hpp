#ifndef CHARACTER_HEALTHSYSTEM_HPP
#define CHARACTER_HEALTHSYSTEM_HPP

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
namespace Character {
class HealthSystem {

public:
    HealthSystem(int maxHp, int currentHp);
    ~HealthSystem();

    int GetCurrentHealth() const { return m_CurrentHealth; }
    int GetMaxHealth() const { return m_MaxHealth; }
    void SetCurrentHealth(int value);
    void SetMaxHealth(int value);
    void ModifyCurrentHealth(int addValue);
    void ModifyMaxHealth(int addValue);
    void BindOnCurrentHealthChange(
        const std::string &eventId,
        std::function<void(int, int)> onCurrentHealthChange);

    void BindOnMaxHealthChange(const std::string &eventId,
                               std::function<void(int, int)> onMaxHealthChange);

    void UnBindOnCurrentHealthChange(const std::string &eventId);

    void UnBindOnMaxHealthChange(const std::string &eventId);

private:
    std::unordered_map<std::string, std::function<void(int, int)>>
        m_OnCurrentHealthChange;
    std::unordered_map<std::string, std::function<void(int, int)>>
        m_OnMaxHealthChange;

    int m_MaxHealth;
    int m_CurrentHealth;
};
} // namespace Character

#endif
