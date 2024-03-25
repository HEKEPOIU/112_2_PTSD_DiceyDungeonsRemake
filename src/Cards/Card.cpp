#include "Cards/Card.hpp"
#include "Cards/CardRequireSlot.hpp"

namespace Cards {

bool Card::IsFit() {
    for (auto slot : m_CardRequireSlot) {
        if (!slot->IsFit(m_Size)) {
            return false;
        }
    }
    return true;
}

} // namespace Cards
