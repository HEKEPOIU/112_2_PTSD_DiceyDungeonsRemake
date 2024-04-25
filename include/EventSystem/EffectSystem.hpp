#ifndef EVENTSYSTEM_EFFECTSYSTEM_HPP
#define EVENTSYSTEM_EFFECTSYSTEM_HPP

#include <functional>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace EventSystem {
class EffectSystem {
public:
    enum class BattleEffect {
        SHIELD,
        FIRE,
    };
    struct BattleEffectInform {
        BattleEffect effect;
        int passRound;
    };

    EffectSystem(){};
    ~EffectSystem() { m_OnEffectChange.clear(); };

    void ApplyEffect(BattleEffect effect, int amount) {
        int oldValue = GetEffectAmount(effect);
        if (oldValue == 0) {
            // First time
            m_EffectCounter[effect] = 0;
        }
        m_EffectMap[effect] = oldValue + amount;
        if (m_EffectMap.at(effect) <= 0) {
            m_EffectMap.erase(effect);
            m_EffectCounter.erase(effect);
        }
        if (!m_OnEffectChange.empty()) {
            for (auto OnEffectChange : m_OnEffectChange) {
                OnEffectChange.second(effect, oldValue,
                                      GetEffectAmount(effect));
            }
        }
    };
    int GetEffectAmount(BattleEffect effect) const {
        auto it = m_EffectMap.find(effect);
        if (it == m_EffectMap.end()) {
            return 0;
        }
        return m_EffectMap.at(effect);
    }

    void BindOnEffectChange(
        const std::string &eventId,
        std::function<void(BattleEffect, int, int)> OnEffectChange) {
        m_OnEffectChange[eventId] = OnEffectChange;
    }

    void UnBindOnEffectChange(const std::string &eventId) {
        m_OnEffectChange.erase(eventId);
    }

    void EffectUpdate() {
        std::vector<BattleEffect> removeEffect;
        for (auto it : m_EffectMap) {
            m_EffectCounter[it.first] += 1;
            if (m_EffectCounter[it.first] >= 2) {
                removeEffect.push_back(it.first);
            }
        }
        for (auto it : removeEffect) {
            ApplyEffect(it, -1);
        }
    }

private:
    std::unordered_map<BattleEffect, int> m_EffectMap;
    std::unordered_map<BattleEffect, int> m_EffectCounter;

    // Return - or 0 on Remove Effect.
    std::unordered_map<std::string, std::function<void(BattleEffect, int, int)>>
        m_OnEffectChange{};
};
} // namespace EventSystem

#endif
