#include "App.hpp"

#include "Cards/Variant/SwordCard.hpp"
#include "Character/Dices/Warrior.hpp"
#include "ResourceConfig.hpp"
#include "UI/CardsRenderer/CardRenderer.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include <memory>

void App::Start() {
    LOG_TRACE("Start");
    m_CurrentState = State::UPDATE;
    m_PlayerDice = std::make_shared<Character::Dices::Warrior>(
        "Thief", 1, 24, 24,
        RESOURCE_DIR "/graphics/characters/thief/static_1080.png");
    m_TestEnemy = std::make_shared<Character::Enemy>(
        "frog", 1, 12, 12, ENEMY_DIR + "/frog/static_1080.png");

    m_BattleSystem = std::make_shared<EventSystem::BattleSystem>(
        nullptr, m_PlayerDice, m_TestEnemy);

    auto cardRenderTest = std::make_shared<UI::CardsRenderer::CardRenderer>(
        std::make_shared<Cards::Variant::SwordCard>(1, 2));

    m_Root->AddChild(m_PlayerDice);
    m_Root->AddChild(m_TestEnemy);
    m_Root->AddChild(m_BattleSystem);
    m_Root->AddChild(cardRenderTest);
    m_BattleSystem->EventStart();
}

void App::Update() {

    // TODO: do your things here and delete this line <3

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    m_Root->Update();
    m_BattleSystem->EventUpdate();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
