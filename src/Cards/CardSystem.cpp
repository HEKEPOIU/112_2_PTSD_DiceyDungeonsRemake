#include "Cards/CardSystem.hpp"
#include <cstddef>

namespace Cards {
CardSystem::CardSystem(size_t sizeX, size_t sizeY)
    : m_MaxSize(sizeX * sizeY) {}

} // namespace Cards
