#ifndef CHARACTER_ENEMYS_ENEMYFACTORY_HPP
#define CHARACTER_ENEMYS_ENEMYFACTORY_HPP

#include "Character/Enemy.hpp"
#include <functional>
#include <memory>
#include <random>
#include <vector>
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

    static std::shared_ptr<Enemy>
    GetRandomEnemy(const std::vector<int> &randomRange) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<unsigned short> range(
            0, randomRange.size() - 1);
        int idIndex = range(gen);
        return m_Creators[randomRange[idIndex]]();
    }

private:
    static inline std::unordered_map<int, Creator> m_Creators{};
};
}; // namespace Character::Enemys

#endif
