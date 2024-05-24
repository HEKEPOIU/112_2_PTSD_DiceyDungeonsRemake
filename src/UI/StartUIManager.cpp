#include "UI/StartUIManager.hpp"
#include "GameCore/GameManager.hpp"
#include "Util/GameObject.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/SpriteSheet.hpp"
#include <memory>

namespace UI {

StartUIManager::StartUIManager(GameCore::GameManager &context)
    : m_CurrentState(context.GetCurrentGameState()),
      m_Context(context) {}

void StartUIManager::Update() {
    if (!isInit) {
        return;
    }

    switch (m_CurrentState) {

    case GameCore::GameStates::TITLESTATE:
        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
            if (m_StartGameBtn->IsOnTop(Util::Input::GetCursorPosition())) {
                m_Context.ChangeStates(GameCore::GameStates::CHARACTERSELECT);
            }
            if (m_EndGameBtn->IsOnTop(Util::Input::GetCursorPosition())) {
                m_Context.EndGame();
            }
        }
        break;
    case GameCore::GameStates::CHARACTERSELECT:
    default:
        break;
    }
}

void StartUIManager::OnGameStatesChange(GameCore::GameStates oldState,
                                        GameCore::GameStates newState) {
    if (oldState != newState) {
        // Unbind Last
    }
    m_CurrentState = newState;
    switch (m_CurrentState) {
    case GameCore::GameStates::TITLESTATE:
        DisplayTitleUi();

        break;
    case GameCore::GameStates::CHARACTERSELECT:
        DisableTitleUI();
        break;
    default:
        break;
    }
    isInit = true;
}

void StartUIManager::DisplayTitleUi() {
    SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/TitleScene.png"));

    m_StartGameBtn = std::make_shared<Util::GameObject>();

    m_StartGameBtn->SetZIndex(GetZIndex() + 1);
    auto startGameBtn =
        std::make_shared<Util::SpriteSheet>(RESOURCE_DIR "/graphics/pack4.png");
    startGameBtn->SetDrawRect({501, 153, 610, 152});
    m_StartGameBtn->SetDrawable(startGameBtn);
    m_StartGameBtn->m_Transform.translation = {605.5, -124};
    m_StartGameBtn->m_Transform.scale = {.5, .5};
    auto startGameBtnText =
        std::make_shared<Util::Text>(RESOURCE_DIR "/NotoSans-Bold.ttf", 40,
                                     "PLAY", Util::Color(255, 255, 255));
    auto startGameBtnTextObj = std::make_shared<Util::GameObject>();
    startGameBtnTextObj->SetDrawable(startGameBtnText);
    startGameBtnTextObj->m_Transform.translation = {615.5, -120};
    startGameBtnTextObj->SetZIndex(GetZIndex() + 2);
    m_StartGameBtn->AddChild(startGameBtnTextObj);
    AddChild(m_StartGameBtn);

    m_EndGameBtn = std::make_shared<Util::GameObject>();

    m_EndGameBtn->SetZIndex(GetZIndex() + 1);
    auto endGameBtn =
        std::make_shared<Util::SpriteSheet>(RESOURCE_DIR "/graphics/pack4.png");
    endGameBtn->SetDrawRect({501, 153, 610, 152});
    m_EndGameBtn->SetDrawable(startGameBtn);
    m_EndGameBtn->m_Transform.translation = {605.5, -424};
    m_EndGameBtn->m_Transform.scale = {.5, .5};
    auto endGameBtnText =
        std::make_shared<Util::Text>(RESOURCE_DIR "/NotoSans-Bold.ttf", 40,
                                     "QUIT", Util::Color(255, 255, 255));
    auto endGameBtnTextObj = std::make_shared<Util::GameObject>();
    endGameBtnTextObj->SetDrawable(endGameBtnText);
    endGameBtnTextObj->m_Transform.translation = {615.5, -420};
    endGameBtnTextObj->SetZIndex(GetZIndex() + 2);
    m_EndGameBtn->AddChild(endGameBtnTextObj);
    AddChild(m_EndGameBtn);
}

void StartUIManager::DisableTitleUI() {
    SetDrawable(nullptr);
    RemoveChild(m_EndGameBtn);
    RemoveChild(m_StartGameBtn);
}

} // namespace UI
