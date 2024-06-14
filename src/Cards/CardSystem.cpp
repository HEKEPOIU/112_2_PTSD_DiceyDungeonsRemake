#include "Cards/CardSystem.hpp"
#include "Cards/Card.hpp"
#include "Cards/CardFactory.hpp"
#include <cstddef>
#include <memory>

namespace Cards {
CardSystem::CardSystem(size_t sizeX, size_t sizeY)
    : m_MaxSize(sizeX * sizeY) {
    m_CardMap.resize(sizeX);
    for (auto &info : m_CardMap) {
        info.resize(sizeY);
    }
}

bool CardSystem::AddCardById(int id) {
    auto card = CardFactory::CreateCard(id);
    return AddCard(card);
}

bool CardSystem::AddRandomCard(){
    auto card = CardFactory::CreateRandomCard();
    return AddCard(card);
}

bool CardSystem::AddCard(std::shared_ptr<Card> card){
    std::vector<glm::ivec2> cardPos = GetAvailableCardPos(card->GetSize());
    if (cardPos.empty()) {
        return false;
    }
    for (auto pos : cardPos) {
        m_CardMap[pos.x][pos.y] = card;
    }
    return true;
}

// This implementation ugly the fuck,
const std::vector<glm::ivec2> CardSystem::GetAvailableCardPos(int size) {
    switch (size) {
    case 1:
        for (size_t x = 0; x < m_CardMap.size(); x++) {
            for (size_t y = 0; y < m_CardMap[0].size(); y++) {
                if (m_CardMap[x][y] == nullptr) {
                    return {{x, y}};
                }
            }
        }
        break;
    case 2:
        for (size_t x = 0; x < m_CardMap.size(); x++) {
            for (size_t y = 0; y < m_CardMap[0].size() - 1; y++) {
                if (m_CardMap[x][y] == nullptr &&
                    m_CardMap[x][y + 1] == nullptr) {
                    return {{x, y}, {x, y + 1}};
                }
            }
        }
        break;
    default:
        throw std::invalid_argument("Card size > 2 in not supported");
        return {};
        break;
    }
    // "Unable to find available card position"
    return {};
};

} // namespace Cards
