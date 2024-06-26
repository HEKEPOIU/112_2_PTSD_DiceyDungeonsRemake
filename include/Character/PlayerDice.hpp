#ifndef CHARACTER_PLAYERDICE_HPP
#define CHARACTER_PLAYERDICE_HPP

#include "Cards/Card.hpp"
#include "Cards/CardSystem.hpp"
#include "Character/BaseCharacter.hpp"
#include <array>
#include <cwchar>
#include <memory>

namespace Character {
class PlayerDice : public BaseCharacter {
public:
    PlayerDice(const std::string &name, int level, int maxHp, int currentHp,
               const std::string &path, const std::string &levelImagePath);

    virtual void RoundStart(EventSystem::BattleSystem &currentBattle) override;
    virtual void RoundUpdate(EventSystem::BattleSystem &currentBattle) override;
    virtual void RoundEnd(EventSystem::BattleSystem &currentBattle) override;
    virtual void SetBattlePosition() override;
    void LevelUp();
    int GetCurrentLevelUpArr() { return m_LevelUpArr[m_Level - 1]; };
    void SetExp(int newExp);
    int GetExp() { return m_CurrentExp; };

    bool AddCard(std::shared_ptr<Cards::Card>& card);
protected:
    std::unique_ptr<Cards::CardSystem> m_BagCards =
        std::make_unique<Cards::CardSystem>(4, 5);
    int m_Money = 0;
    int m_CurrentExp = 0;
    static constexpr std::array<int, 5> m_LevelUpArr{2, 4, 7, 14, 18};
    static constexpr std::array<int, 6> m_LimitBreakHp{8, 9, 10, 12, 12, 13};
    static constexpr std::array<int, 6> m_HpPerLevel{24, 28, 32, 36, 40, 44};
};
} // namespace Character

#endif
