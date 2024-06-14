#include "EventSystem/EndSystem.hpp"
#include "GameCore/GameManager.hpp"
#include "GameCore/MainGame.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Text.hpp"
#include <memory>

namespace EventSystem {

EndSystem::EndSystem(GameCore::MainGame &mainGame)
    : BaseEventSystem(mainGame) {
    SetDrawable(std::make_shared<Util::Image>(
        RESOURCE_DIR
        "/graphics/cutscenes/endgame/scene_2/background_1080.png"));
}
void EndSystem::EventStart() {
    m_Character = std::make_shared<Util::GameObject>();
    m_Character->SetDrawable(m_MainGame.GetPlayerDice()->GetLevelDrawable());
    m_Character->m_Transform.scale = {4, 4};
    m_Character->m_Transform.translation = {0, -100};
    AddChild(m_Character);
    m_Character->SetZIndex(5);

    m_WinIcon = std::make_shared<Util::GameObject>();
    m_WinIcon->SetDrawable(
        std::make_shared<Util::Text>(RESOURCE_DIR "/NotoSans-Bold.ttf", 120,
                                     "WIN !", Util::Color(222, 222, 29)));
    m_WinIcon->m_Transform.translation = {0, 400};
    AddChild(m_WinIcon);
    m_WinIcon->SetZIndex(5);

    m_TitleBtn = std::make_shared<Util::GameObject>();
    m_EndGameBtn = std::make_shared<Util::GameObject>();

    m_EndGameBtn->SetZIndex(GetZIndex() + 1);
    auto endGameBtn =
        std::make_shared<Util::SpriteSheet>(RESOURCE_DIR "/graphics/pack4.png");
    endGameBtn->SetDrawRect({501, 153, 610, 152});
    m_EndGameBtn->SetDrawable(endGameBtn);
    m_EndGameBtn->m_Transform.translation = {0, 100};
    m_EndGameBtn->m_Transform.scale = {.5, .5};
    auto endGameBtnText =
        std::make_shared<Util::Text>(RESOURCE_DIR "/NotoSans-Bold.ttf", 40,
                                     "QUIT", Util::Color(255, 255, 255));
    auto endGameBtnTextObj = std::make_shared<Util::GameObject>();
    endGameBtnTextObj->SetDrawable(endGameBtnText);
    endGameBtnTextObj->m_Transform.translation = {10, 104};
    endGameBtnTextObj->SetZIndex(GetZIndex() + 2);
    m_EndGameBtn->AddChild(endGameBtnTextObj);
    AddChild(m_EndGameBtn);

    m_TitleBtn = std::make_shared<Util::GameObject>();

    m_TitleBtn->SetZIndex(GetZIndex() + 1);
    auto titleBtn =
        std::make_shared<Util::SpriteSheet>(RESOURCE_DIR "/graphics/pack4.png");
    titleBtn->SetDrawRect({501, 153, 610, 152});
    m_TitleBtn->SetDrawable(titleBtn);
    m_TitleBtn->m_Transform.translation = {0, 200};
    m_TitleBtn->m_Transform.scale = {.5, .5};
    auto titleBtnText =
        std::make_shared<Util::Text>(RESOURCE_DIR "/NotoSans-Bold.ttf", 40,
                                     "TITLE", Util::Color(255, 255, 255));
    auto titleBtnTextObj = std::make_shared<Util::GameObject>();
    titleBtnTextObj->SetDrawable(titleBtnText);
    titleBtnTextObj->m_Transform.translation = {10, 204};
    titleBtnTextObj->SetZIndex(GetZIndex() + 2);
    m_TitleBtn->AddChild(titleBtnTextObj);
    AddChild(m_TitleBtn);
}
void EndSystem::EventUpdate() {
    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
        if (m_EndGameBtn->IsOnTop(Util::Input::GetCursorPosition())) {
            m_MainGame.EndGame();
        }
        if (m_TitleBtn->IsOnTop(Util::Input::GetCursorPosition())) {
            m_MainGame.ChangeGameState(GameCore::GameStates::TITLESTATE);
        }
    }
}
void EndSystem::EventEnd() {}
} // namespace EventSystem
