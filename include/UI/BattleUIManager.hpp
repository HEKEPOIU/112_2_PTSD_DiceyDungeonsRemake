#ifndef UI_BATTLEUIMANAGER_HPP
#define UI_BATTLEUIMANAGER_HPP

#include "UI/Utils/Slider.hpp"
#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include <memory>

namespace EventSystem {
class BattleSystem;
}

namespace UI {
class BattleUIManager : public Util::GameObject {
public:
    BattleUIManager(EventSystem::BattleSystem &currentBattle);
    ~BattleUIManager();

private:
    void OnCurrentHealthChange(int oldHealth, int newHealth);
    void OnMaxHealthChange(int oldHealth, int newHealth);
    void SetPlayerUIInform();
    std::shared_ptr<Utils::Slider> m_Slider;
    std::shared_ptr<Util::Text> m_PlayerName;
    EventSystem::BattleSystem &m_CurrentBattle;
};
} // namespace UI

#endif
