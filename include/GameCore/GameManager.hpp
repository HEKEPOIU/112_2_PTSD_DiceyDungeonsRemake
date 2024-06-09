#ifndef GAMECORE_GAMEMANARGER_HPP
#define GAMECORE_GAMEMANARGER_HPP

#include "Character/PlayerDice.hpp"
#include "GameCore/MainGame.hpp"
#include "UI/StartUIManager.hpp"
#include <memory>

class App;
namespace GameCore {
enum class GameStates { TITLESTATE, CHARACTERSELECT, MAINGAME };
class GameManager : public Util::GameObject {
public:
    explicit GameManager(App &context, GameStates startState);

    void UpdateGame();
    GameStates GetCurrentGameState() { return m_CurrentStates; }
    void OnGameStatesChange(GameStates oldState, GameStates newState);
    void StartMainGame(std::shared_ptr<Character::PlayerDice> playerDice);
    void ChangeStates(GameStates newState);
    void EndGame();

private:
    GameStates m_CurrentStates;
    App &m_Context;
    std::shared_ptr<MainGame> m_MainGame;
    std::shared_ptr<UI::StartUIManager> m_StartUIManager;
};
} // namespace GameCore

#endif // DEBUG
