#ifndef UI_CARDSRENDERER_CARDRENDERER_HPP
#define UI_CARDSRENDERER_CARDRENDERER_HPP

#include "Cards/Card.hpp"
#include "UI/CardsRenderer/RequireSlotRenderer.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <cstddef>
#include <glm/fwd.hpp>
#include <memory>
#include <unordered_map>
#include <vector>
namespace UI::CardsRenderer {
class CardRenderer : public Util::GameObject {
public:
    CardRenderer(const std::shared_ptr<Cards::Card> &card);

    void SetTranslate(const glm::vec2 &translate);
    void
    Update(const std::shared_ptr<DiceUtils::Dice> &dice,
           const std::shared_ptr<EventSystem::BattleSystem> &currentBattle) {
        for (auto slotRender : m_SlotObjects) {
            if (slotRender->IsOnTop(dice->GetTransform().translation)) {
                slotRender->Use(dice, currentBattle);
                break;
            }
        }
    };

private:
    void InitImageMap();
    void SetUpTransform(const std::shared_ptr<Cards::Card> &card);
    int m_Size;

    std::vector<std::shared_ptr<RequireSlotRenderer>> m_RequireSlotRenderer;
    std::shared_ptr<Util::GameObject> m_NameObject;
    std::shared_ptr<Util::GameObject> m_DescriptionObject;
    std::vector<std::shared_ptr<UI::CardsRenderer::RequireSlotRenderer>>
        m_SlotObjects;
    static std::unordered_map<Cards::CardColor, std::shared_ptr<Util::Image>>
        m_ImageMap;
    inline static std::vector<glm::vec2> m_NameOffset = {{15, 125}, {15, 200}};
    inline static std::vector<glm::vec2> m_DescriptionOffset = {{15, -60},
                                                                {15, -125}};
    inline static std::vector<glm::vec2> m_SlotOffset = {{5, 15}, {5, 0}};
};
} // namespace UI::CardsRenderer

#endif
