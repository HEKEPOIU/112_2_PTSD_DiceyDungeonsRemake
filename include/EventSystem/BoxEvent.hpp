#ifndef EVENTSYSTEM_BOXEVENT_HPP
#define EVENTSYSTEM_BOXEVENT_HPP

#include "Cards/CardFactory.hpp"
#include "EventSystem/BaseEventSystem.hpp"
#include "GameCore/MainGame.hpp"
#include "UI/CardsRenderer/CardRenderer.hpp"
#include "Util/GameObject.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include <iostream>
#include <memory>
#include <ostream>
namespace EventSystem {
class BoxEvent : public BaseEventSystem {
public:
    BoxEvent(GameCore::MainGame &mainGame)
        : BaseEventSystem(mainGame) {
        SetDrawable(std::make_shared<Util::Image>(
            RESOURCE_DIR
            "/graphics/backgrounds/overworld/ice/static_1080.png"));
    }
    void EventStart() override {
        auto card = Cards::CardFactory::CreateRandomCard();
        bool isWork = m_MainGame.GetPlayerDice()->AddCard(card);
        std::cout << isWork <<std::endl;
        m_CardRenderer =
            std::make_shared<UI::CardsRenderer::CardRenderer>(card);
        AddChild(m_CardRenderer);
        m_CardRenderer->SetIndexWithChild(GetZIndex() + 1);
        m_ObjToClick = std::make_shared<Util::GameObject>();
        m_ObjToClick->SetZIndex(GetZIndex() + 1);
        auto endGameBtn = std::make_shared<Util::SpriteSheet>(
            RESOURCE_DIR "/graphics/pack4.png");
        endGameBtn->SetDrawRect({501, 153, 610, 152});
        m_ObjToClick->SetDrawable(endGameBtn);
        m_ObjToClick->m_Transform.translation = {0, -300};
        m_ObjToClick->m_Transform.scale = {.5, .5};
        auto endGameBtnText =
            std::make_shared<Util::Text>(RESOURCE_DIR "/NotoSans-Bold.ttf", 40,
                                         "QUIT", Util::Color(255, 255, 255));
        auto endGameBtnTextObj = std::make_shared<Util::GameObject>();
        endGameBtnTextObj->SetDrawable(endGameBtnText);
        endGameBtnTextObj->m_Transform.translation = {10, -296};
        endGameBtnTextObj->SetZIndex(GetZIndex() + 2);
        m_ObjToClick->AddChild(endGameBtnTextObj);
        AddChild(m_ObjToClick);
    };
    void EventUpdate() override {
        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
            if (m_ObjToClick->IsOnTop(Util::Input::GetCursorPosition())) {
                RemoveChild(m_CardRenderer);
                m_CardRenderer = nullptr;
                m_MainGame.EndEvent();
            }
        }
    };
    void EventEnd() override {};

private:
    std::shared_ptr<Util::GameObject> m_ObjToClick;
    std::shared_ptr<UI::CardsRenderer::CardRenderer> m_CardRenderer;
};
} // namespace EventSystem
#endif
