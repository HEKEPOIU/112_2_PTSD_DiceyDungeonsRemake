#ifndef CARDS_CARDSYSTEM_HPP
#define CARDS_CARDSYSTEM_HPP

#include "Cards/Card.hpp"
#include <vector>

namespace Cards {
class CardSystem {

public:
    const Card &GetCard(int id);

    int SetCardPostion(const Card &targetCard);

private:
    std::vector<Card> m_CardLists;
};
} // namespace Cards

#endif
