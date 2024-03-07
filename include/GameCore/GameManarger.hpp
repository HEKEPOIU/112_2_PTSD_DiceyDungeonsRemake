#ifndef GAMECORE_GAMEMANARGER_HPP
#define GAMECORE_GAMEMANARGER_HPP

namespace GameCore {
class GameManager {
public:
    enum class GameStates { TITLESTATE, CHARACTERSELECT, MAINGAME };

    explicit GameManager(GameStates startState);

    void UpdateGame();
    void OnGameStatesChange();

private:
    GameStates m_CurrentStates;
};
} // namespace GameCore

#endif // DEBUG
