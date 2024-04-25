#include "UI/Utils/EffectIcon.hpp"

namespace UI::Utils {
EffectIcon::EffectIcon(EventSystem::EffectSystem::BattleEffect effect,
                       int amount, int zIndex)
    : m_Effect(effect),
      m_CurrentAmount(amount) {
    if (image.empty()) {
        InitImage();
    }
    m_Text = std::make_shared<Util::Text>(RESOURCE_DIR "/NotoSans-Regular.ttf",
                                          35, std::to_string(amount),
                                          Util::Color{255, 255, 255});
    m_TextObject->SetDrawable(m_Text);
    SetDrawable(image.at(m_Effect));
    AddChild(m_TextObject);
    m_Transform.scale = {0.4, 0.4};
    SetZIndex(zIndex);
    m_TextObject->SetZIndex(zIndex);
    SetPosition({0, 0});
}

void EffectIcon::InitImage() {
    image[EventSystem::EffectSystem::BattleEffect::SHIELD] =
        std::make_shared<Util::SpriteSheet>(RESOURCE_DIR
                                            "/graphics/ui/symbols.png");
    image[EventSystem::EffectSystem::BattleEffect::SHIELD]->SetDrawRect(
        {1443, 0, 86, 90});

    image[EventSystem::EffectSystem::BattleEffect::FIRE] =
        std::make_shared<Util::SpriteSheet>(RESOURCE_DIR
                                            "/graphics/ui/symbols.png");
    image[EventSystem::EffectSystem::BattleEffect::FIRE]->SetDrawRect(
        {903, 0, 86, 90});
}

std::unordered_map<EventSystem::EffectSystem::BattleEffect,
                   std::shared_ptr<Util::SpriteSheet>>
    EffectIcon::image{};
} // namespace UI::Utils
