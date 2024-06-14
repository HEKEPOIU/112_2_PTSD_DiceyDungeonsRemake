#include "Cards/Card.hpp"
#include "Cards/CardRequireSlot.hpp"
#include "Util/Logger.hpp"
#include <iostream>

namespace Cards {

bool Card::IsFit() const {
    for (auto slot : m_CardRequireSlot) {
        if (!slot->IsFit(slot->GetContainDiceNum())) {
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
    std::cout << m_OnCardUsed.size() << std::endl;
    auto it = m_OnCardUsed.find(eventId);
    if (it != m_OnCardUsed.end()) {
        m_OnCardUsed.erase(it);
    }
    std::cout << m_OnCardUsed.size() << std::endl;
}

} // namespace Cards
