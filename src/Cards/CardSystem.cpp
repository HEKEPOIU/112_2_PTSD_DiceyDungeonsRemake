#include "Cards/CardSystem.hpp"
#include <cstddef>

namespace Cards {
CardSystem::CardSystem(size_t sizeX, size_t sizeY) {
    for (size_t i = 0; i < sizeX; i++) {
        m_CardLists.push_back({});
        for (size_t u = 0; u < sizeY; u++) {
            m_CardLists[i].push_back({});
        }
    }
}

} // namespace Cards
