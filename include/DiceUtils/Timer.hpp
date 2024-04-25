#ifndef DICEUTILS_TIMER_HPP
#define DICEUTILS_TIMER_HPP

#include "Util/Time.hpp"
#include <functional>
namespace DiceUtils {
class Timer {

public:
    Timer(float targetTime)
        : m_IsStarted(false),
          m_CurrentTime(0),
          m_TargetTime(targetTime){};

    void StartTimer() { m_IsStarted = true; };
    void SetTime(float time) { m_TargetTime = time; };
    void Update() {
        if (!m_IsStarted)
            return;

        m_CurrentTime += Util::Time::GetDeltaTime();
        if (m_CurrentTime >= m_TargetTime) {
            ResetTime();
            m_IsStarted = false;
            OnTimerEnd();
        }
    }
    void ResetTime() { m_CurrentTime = 0; };

    void SetOnTimerEnd(std::function<void()> func) { OnTimerEnd = func; }
    void RemoveOnTimerEnd() { OnTimerEnd = nullptr; }

private:
    bool m_IsStarted;
    float m_CurrentTime;
    float m_TargetTime;
    std::function<void()> OnTimerEnd;
};
} // namespace DiceUtils

#endif
