#ifndef CARDS_CARDSYSTEM_HPP
#define CARDS_CARDSYSTEM_HPP

#include "Cards/Card.hpp"
#include <cstddef>
#include <glm/fwd.hpp>
#include <vector>

namespace Cards {
class CardSystem {

public:
    CardSystem(size_t sizeX, size_t sizeY);
    const Card &GetCard(int id);

    int SetCardPostion(const Card &targetCard);

private:
    std::vector<std::vector<Card>> m_CardLists{};
};
} // namespace Cards

#endif
