#ifndef UI_UTILS_EFFECTBAR_HPP
#define UI_UTILS_EFFECTBAR_HPP

#include "EventSystem/EffectSystem.hpp"
#include "UI/Utils/EffectIcon.hpp"
#include "Util/GameObject.hpp"
#include <glm/fwd.hpp>
#include <map>
#include <memory>
#include <vector>
namespace UI::Utils {
class EffectBar : public Util::GameObject {
public:
    EffectBar();
    void ShowEffect(EventSystem::EffectSystem::BattleEffect effect,
                    int oldValue, int newValue);
    void SetPosition(glm::vec2 pos);
    void AddIcon(const EventSystem::EffectSystem::BattleEffect &effect,
                 int initValue);
    void
    RemoveIcon(const std::vector<std::shared_ptr<EffectIcon>>::iterator &it);

private:
    void LayoutIcon();

    std::vector<std::shared_ptr<EffectIcon>> m_Icons;
};
} // namespace UI::Utils

#endif
