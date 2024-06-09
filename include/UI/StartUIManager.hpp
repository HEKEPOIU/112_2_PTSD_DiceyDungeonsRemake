#ifndef UI_TITLEUIMANAGER_HPP
#define UI_TITLEUIMANAGER_HPP

#include "Util/GameObject.hpp"
namespace GameCore {
class GameManager;
enum class GameStates;
} // namespace GameCore

namespace UI {
class StartUIManager : public Util::GameObject {

public:
    StartUIManager(GameCore::GameManager &context);
    void Update();
    void OnGameStatesChange(GameCore::GameStates oldState,
                            GameCore::GameStates newState);

private:
    void DisplayTitleUi();
    void DisableTitleUI();
    void DisplaySelectUi();
    void DisableSelectUi();

    bool isInit = false;
    GameCore::GameStates m_CurrentState;
    GameCore::GameManager &m_Context;
    std::shared_ptr<Util::GameObject> m_StartGameBtn;
    std::shared_ptr<Util::GameObject> m_CharacterSelectBtn;
    std::shared_ptr<Util::GameObject> m_TitleBtn;
    std::shared_ptr<Util::GameObject> m_EndGameBtn;
};
} // namespace UI

#endif
