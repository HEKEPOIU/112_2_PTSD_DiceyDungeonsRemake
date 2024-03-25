#ifndef UI_BATTLEUIMANAGER_HPP
#define UI_BATTLEUIMANAGER_HPP

#include "UI/Utils/Slider.hpp"
#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include <memory>
#include <string>

namespace EventSystem {
class BattleSystem;
}

namespace UI {
// I Hate UI in pure Code, special on I need recreate everything, fk.
class BattleUIManager : public Util::GameObject {
public:
    BattleUIManager(EventSystem::BattleSystem &currentBattle);
    ~BattleUIManager();

    void Update();

private:
    void OnCurrentHealthChange(int oldHealth, int newHealth);
    void OnMaxHealthChange(int oldHealth, int newHealth);
    void SetBattleBarInform(const std::shared_ptr<Utils::Slider> &bar,
                            const std::string &name, const glm::vec2 &pos,
                            const glm::vec2 &scale);

    std::shared_ptr<Utils::Slider> m_PlayerHpBar;
    std::shared_ptr<Util::Text> m_PlayerName;
    std::shared_ptr<Utils::Slider> m_EnemyHpBar;
    std::shared_ptr<Util::Text> m_EnemyName;
    EventSystem::BattleSystem &m_CurrentBattle;
};
} // namespace UI

#endif
