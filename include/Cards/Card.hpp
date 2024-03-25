#ifndef CARDS_CARD_HPP
#define CARDS_CARD_HPP
#include <memory>
#include <string>
#include <vector>

namespace EventSystem {
class BattleSystem;
}
namespace Cards {
class CardRequireSlot;
}

namespace Cards {
enum class CardColor { RED, YELLOW, BLUE, GREEN, GREY, ORANGE, PINK, PURPLE };
class Card {
public:
    Card(int id, int size)
        : m_Id(id),
          m_Size(size) {}

    const std::vector<std::shared_ptr<Cards::CardRequireSlot>> &
    GetRequireSlot() const {
        return m_CardRequireSlot;
    }
    virtual void Use(const std::shared_ptr<EventSystem::BattleSystem>
                         &currentBattle) const = 0;

    bool IsFit();

    void AddRequireSlot(const std::shared_ptr<Cards::CardRequireSlot> &slot) {
        m_CardRequireSlot.push_back(slot);
    }

    int GetId() const { return m_Id; }
    const std::string &GetCardName() const { return m_CardName; }
    const std::string &GetCardDescription() const { return m_CardDescription; }
    int GetSize() const { return m_Size; }
    CardColor GetColor() const { return m_Color; }

protected:
    int m_Id;
    int m_Size;
    CardColor m_Color;
    std::string m_CardName;
    std::string m_CardDescription;
    std::vector<std::shared_ptr<Cards::CardRequireSlot>> m_CardRequireSlot{};
};
} // namespace Cards

#endif
