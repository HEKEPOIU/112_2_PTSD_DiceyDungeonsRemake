#ifndef UI_UTILS_EFFECTICON_HPP
#define UI_UTILS_EFFECTICON_HPP

#include "EventSystem/EffectSystem.hpp"
#include "Util/GameObject.hpp"
#include "Util/SpriteSheet.hpp"
#include "Util/Text.hpp"
#include <memory>
#include <string>
#include <unordered_map>

namespace UI::Utils {
class EffectIcon : public Util::GameObject {

public:
    EffectIcon(EventSystem::EffectSystem::BattleEffect effect, int amount,
               int zIndex);

    void SetAmount(int value) {
        m_CurrentAmount = value;
        m_Text->SetText(std::to_string(m_CurrentAmount));
    };
    int GetAmount() { return m_CurrentAmount; };
    EventSystem::EffectSystem::BattleEffect GetEffect() { return m_Effect; };

    void SetPosition(glm::vec2 pos) {
        m_Transform.translation = pos;
        m_TextObject->m_Transform.translation = {
            m_Transform.translation.x + TextOffset, m_Transform.translation.y};
    }

private:
    void InitImage();
    static std::unordered_map<EventSystem::EffectSystem::BattleEffect,
                              std::shared_ptr<Util::SpriteSheet>>
        image;
    std::shared_ptr<Util::GameObject> m_TextObject =
        std::make_shared<Util::GameObject>();
    std::shared_ptr<Util::Text> m_Text;
    EventSystem::EffectSystem::BattleEffect m_Effect;
    int m_CurrentAmount;
    int TextOffset = 35;
};
} // namespace UI::Utils

#endif
