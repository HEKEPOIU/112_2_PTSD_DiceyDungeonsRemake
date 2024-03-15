#ifndef GAMECORE_GAMEMANARGER_HPP
#define GAMECORE_GAMEMANARGER_HPP

#include "GameCore/MainGame.hpp"
#include <memory>
namespace GameCore {
class GameManager {
public:
    enum class GameStates { TITLESTATE, CHARACTERSELECT, MAINGAME };

    explicit GameManager(GameStates startState);

    void UpdateGame();
    void OnGameStatesChange();

private:
    GameStates m_CurrentStates;
    std::shared_ptr<MainGame> m_MainGame;
};
} // namespace GameCore

#endif // DEBUG
