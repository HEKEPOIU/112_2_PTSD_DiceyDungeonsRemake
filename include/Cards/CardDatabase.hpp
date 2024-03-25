#ifndef CARDS_CARDDATABASE_HPP
#define CARDS_CARDDATABASE_HPP

#include "Cards/Card.hpp"
#include "Cards/Variant/SwordCard.hpp"
#include <algorithm>
#include <memory>
#include <vector>
namespace Cards {
class CardDatabase {

public:
    const std::shared_ptr<Card> &GetCardById(int id) {
        return *std::find_if(m_Cards.begin(), m_Cards.end(),
                             [id](auto card) { return card->GetId() == id; });
    }

private:
    inline static std::vector<std::shared_ptr<Card>> m_Cards{
        std::make_shared<Variant::SwordCard>(1, 2),
    };
};
} // namespace Cards

#endif
