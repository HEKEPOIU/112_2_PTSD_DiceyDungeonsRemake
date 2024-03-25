#ifndef CARDS_CARDSYSTEM_HPP
#define CARDS_CARDSYSTEM_HPP

#include "Cards/Card.hpp"
#include <cstddef>
#include <glm/vec2.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

namespace Cards {
class CardSystem {

public:
    struct CardInformation {

        std::vector<glm::ivec2> cardPos;
        std::shared_ptr<Card> card;
    };
    CardSystem(size_t sizeX, size_t sizeY);
    const Card &GetCard(int id);

    void AddCardById(int id);

    const std::vector<CardInformation> &GetCardMap() { return m_CardMap; }

private:
    int m_MaxSize;
    std::vector<CardInformation> m_CardMap{};
};
} // namespace Cards

#endif
