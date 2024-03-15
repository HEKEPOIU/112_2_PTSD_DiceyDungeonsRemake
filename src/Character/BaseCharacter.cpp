#include "Character/BaseCharacter.hpp"
#include "Character/HealthSystem.hpp"
#include "Util/Image.hpp"
#include <glm/fwd.hpp>
#include <glm/gtx/string_cast.hpp>
#include <memory>

namespace Character {

BaseCharacter::BaseCharacter(int level, int maxHp, int currentHp,
                             const std::string &path)
    : m_CharacterImage(std::make_shared<Util::Image>(path)),
      m_HealthSystem(std::make_unique<HealthSystem>(maxHp, currentHp)),
      m_Level(level) {
    SetDrawable(m_CharacterImage);
}

} // namespace Character
