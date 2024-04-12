#ifndef EVENTSYSTEM_EFFECTSYSTEM_HPP
#define EVENTSYSTEM_EFFECTSYSTEM_HPP

#include <unordered_map>

namespace EventSystem {
class EffectSystem {
public:
    enum class BattleEffect {
        SHIELD,

    };
    EffectSystem(){};

    void ApplyEffect(BattleEffect effect, int amount) {
        auto result = m_EffectMap.insert({effect, amount});
        if (!result.second) {
            m_EffectMap[effect] += amount;
        }
    };
    int GetEffectAmount(BattleEffect effect) const {
        auto it = m_EffectMap.find(effect);
        if (it == m_EffectMap.end()) {
            return 0;
        }
        return m_EffectMap.at(effect);
    }
    void RemoveEffectAmount(BattleEffect effect, int amount) {
        auto it = m_EffectMap.find(effect);
        if (it == m_EffectMap.end()) {
            return;
        }
        m_EffectMap[effect] -= amount;
        if (m_EffectMap.at(effect) <= 0) {
            m_EffectMap.erase(effect);
        }
    };

private:
    std::unordered_map<BattleEffect, int> m_EffectMap;
};
} // namespace EventSystem

#endif
