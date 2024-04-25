#include "UI/Utils/EffectBar.hpp"
#include "EventSystem/EffectSystem.hpp"
#include "Util/Logger.hpp"
#include "Util/SpriteSheet.hpp"
#include <algorithm>
#include <cstddef>
#include <memory>

namespace UI::Utils {

EffectBar::EffectBar()
    : Util::GameObject() {
    auto backGround =
        std::make_shared<Util::SpriteSheet>(RESOURCE_DIR "/graphics/pack1.png");
    backGround->SetDrawRect({101, 929, 101, 602});
    SetDrawable(backGround);
    m_Transform.rotation = glm::radians(90.0f);
    m_Transform.scale = {0.5, 0.5};
}

void EffectBar::ShowEffect(EventSystem::EffectSystem::BattleEffect effect,
                           int oldValue, int newValue) {
    std::vector<std::shared_ptr<EffectIcon>>::iterator it =
        std::find_if(m_Icons.begin(), m_Icons.end(),
                     [effect](const std::shared_ptr<EffectIcon> &icon) {
                         return icon->GetEffect() == effect;
                     });
    if (it == m_Icons.end()) {
        if (newValue <= 0) {
            return;
        }
        AddIcon(effect, newValue);

    } else {
        it->get()->SetAmount(newValue);

        if (it->get()->GetAmount() <= 0) {
            RemoveIcon(it);
        }
    }
}

void EffectBar::RemoveIcon(
    const std::vector<std::shared_ptr<EffectIcon>>::iterator &it) {
    RemoveChild(*it);
    m_Icons.erase(it);
    LayoutIcon();
}

void EffectBar::AddIcon(const EventSystem::EffectSystem::BattleEffect &effect,
                        int initValue) {
    auto icon =
        std::make_shared<EffectIcon>(effect, initValue, GetZIndex() + 1);
    m_Icons.push_back(icon);
    AddChild(icon);
    icon->SetPosition(m_Transform.translation);
    LayoutIcon();
}

void EffectBar::SetPosition(glm::vec2 pos) {
    m_Transform.translation = pos;
    LayoutIcon();
}

void EffectBar::LayoutIcon() {
    for (size_t i = 0; i < m_Icons.size(); i++) {
        m_Icons[i]->SetPosition({(m_Transform.translation.x - 115) + (i * 60),
                                 (m_Transform.translation.y)});
    }
}
} // namespace UI::Utils
