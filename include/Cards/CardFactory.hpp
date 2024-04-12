#ifndef CARDS_VARIANT_CARDFACTORY_HPP
#define CARDS_VARIANT_CARDFACTORY_HPP

#include "Cards/Card.hpp"
#include <functional>
#include <memory>
#include <stdexcept>
namespace Cards {
class CardFactory {
public:
    using Creator = std::function<std::shared_ptr<Card>()>;

    // I am not sure if this is the right way to do it, should be a singleton?

    static void RegisterCard(int id, const Creator &creator) {
        m_Creators[id] = creator;
    }

    static std::shared_ptr<Card> CreateCard(int id) {
        if (m_Creators.count(id)) {
            return m_Creators[id]();
        } else {
            throw std::runtime_error("Card not found");
            return nullptr;
        }
    }

private:
    static inline std::unordered_map<int, Creator> m_Creators{};
};
} // namespace Cards

#endif
