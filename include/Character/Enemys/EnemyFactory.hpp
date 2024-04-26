#ifndef CHARACTER_ENEMYS_ENEMYFACTORY_HPP
#define CHARACTER_ENEMYS_ENEMYFACTORY_HPP

#include "Character/Enemy.hpp"
#include <functional>
#include <memory>
namespace Character::Enemys {
class EnemyFactory {
public:
    using Creator = std::function<std::shared_ptr<Enemy>()>;

    // I am not sure if this is the right way to do it, should be a singleton?

    static void RegisterEnemy(int id, const Creator &creator) {
        m_Creators[id] = creator;
    }

    static std::shared_ptr<Enemy> CreateEnemy(int id) {
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
}; // namespace Character::Enemys

#endif
