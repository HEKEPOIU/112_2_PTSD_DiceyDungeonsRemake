#ifndef CARDS_CARDSYSTEM_HPP
#define CARDS_CARDSYSTEM_HPP

#include "Cards/Card.hpp"
#include <cstddef>
#include <glm/vec2.hpp>
#include <memory>
#include <vector>

namespace Cards {
class CardSystem {

public:
    CardSystem(size_t sizeX, size_t sizeY);
    const Card &GetCard(int id);

    bool AddCardById(int id);
    const std::vector<glm::ivec2> GetAvailableCardPos(int size);

    const std::vector<std::vector<std::shared_ptr<Card>>> &GetCardMap() {
        return m_CardMap;
    }

private:
    int m_MaxSize;
    std::vector<std::vector<std::shared_ptr<Card>>> m_CardMap{};
};
} // namespace Cards

#endif
