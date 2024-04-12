#include "Cards/Card.hpp"
#include "Cards/CardRequireSlot.hpp"

namespace Cards {

bool Card::IsFit() const {
    for (auto slot : m_CardRequireSlot) {
        if (!slot->IsFit(m_Size)) {
            return false;
        }
    }
    return true;
}
void Card::BindOnCardUsedEvent(const std::string &eventId,
                               std::function<void()> onCardUsed) {
    auto it = m_OnCardUsed.insert({eventId, onCardUsed});
    if (!it.second) {
        LOG_INFO("CurrentHealthChange Event:{} is already bound", eventId);
        throw std::invalid_argument("Already Bound");
    }
}

void Card::UnBindOnCardUsedEvent(const std::string &eventId) {
    m_OnCardUsed.erase(eventId);
}

} // namespace Cards
