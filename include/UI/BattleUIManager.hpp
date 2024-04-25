#ifndef UI_BATTLEUIMANAGER_HPP
#define UI_BATTLEUIMANAGER_HPP

#include "EventSystem/EffectSystem.hpp"
#include "UI/CardsRenderer/CardRenderer.hpp"
#include "UI/Utils/EffectBar.hpp"
#include "UI/Utils/Slider.hpp"
#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include <memory>
#include <vector>

namespace EventSystem {
class BattleSystem;
enum class BattleStatus;
} // namespace EventSystem

namespace UI {
// I Hate UI in pure Code, special on I need recreate everything, fk.
class BattleUIManager : public Util::GameObject {
public:
    BattleUIManager(EventSystem::BattleSystem &currentBattle);
    ~BattleUIManager();

    void Update();
    void DetectUiClick(const glm::vec2 &pos);
    void OnChangeStatus(EventSystem::BattleStatus oldStatus,
                        EventSystem::BattleStatus newStatus);

    //  It Should not do this But I don't think batter way.
    std::vector<std::shared_ptr<CardsRenderer::CardRenderer>> &
    GetEnemyCardRenderer() {
        return m_EnemyCardRenderers;
    }

private:
    void OnPlayerEffectChange(EventSystem::EffectSystem::BattleEffect effect,
                              int oldValue, int newValue);
    void OnEnemyEffectChange(EventSystem::EffectSystem::BattleEffect effect,
                             int oldValue, int newValue);
    void SetBattleBarInform(const std::shared_ptr<Utils::Slider> &bar,
                            const std::string &name, const glm::vec2 &pos,
                            const glm::vec2 &scale);

    void SetCardRenderer(
        std::vector<std::shared_ptr<CardsRenderer::CardRenderer>>
            &cardRenderers,
        const std::vector<std::vector<std::shared_ptr<Cards::Card>>> &cardMap);
    void SetupEndTurnBtn();

    void BindEvents();

    void SetPlayerUIVisible(bool visible);
    void SetEnemyUIVisible(bool visible);

    std::shared_ptr<Utils::Slider> m_PlayerHpBar;
    std::shared_ptr<Util::Text> m_PlayerName;
    std::shared_ptr<Utils::Slider> m_EnemyHpBar;
    std::shared_ptr<Util::Text> m_EnemyName;
    std::shared_ptr<Util::GameObject> m_EndTurnBtnIcon;
    std::shared_ptr<Util::GameObject> m_EndTurnBtnText;
    std::shared_ptr<Utils::EffectBar> m_EnemyEffectBar =
        std::make_shared<Utils::EffectBar>();
    std::shared_ptr<Utils::EffectBar> m_PlayerEffectBar =
        std::make_shared<Utils::EffectBar>();
    std::vector<std::shared_ptr<CardsRenderer::CardRenderer>>
        m_PlayerCardRenderers;
    std::vector<std::shared_ptr<CardsRenderer::CardRenderer>>
        m_EnemyCardRenderers;
    EventSystem::BattleSystem &m_CurrentBattle;
};
} // namespace UI

#endif
