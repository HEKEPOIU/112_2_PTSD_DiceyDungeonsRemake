#ifndef UI_CARDSRENDERER_CARDRENDERER_HPP
#define UI_CARDSRENDERER_CARDRENDERER_HPP

#include "Cards/Card.hpp"
#include "DiceUtils/Dice.hpp"
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
    ~CardRenderer();

    void SetTranslate(const glm::vec2 &translate);
    void Use(const std::shared_ptr<DiceUtils::Dice> &dice,
             EventSystem::BattleSystem &currentBattle) {
        if (!m_Visible) {
            return;
        }
        for (auto slotRender : m_SlotObjects) {
            if (slotRender->IsOnTop(dice->GetTransform().translation)) {
                slotRender->Use(dice, currentBattle);

                break;
            }
        }
    };

    void OnCardUsed();

    void SetCardVisible(bool visible) {
        m_Visible = visible;
        for (auto child : m_Children) {
            child->SetVisible(visible);
            for (auto childD2 : child->GetChildren()) {
                childD2->SetVisible(visible);
            }
        }
    }

    int GetSize() const { return m_Size; }

    const std::shared_ptr<UI::CardsRenderer::RequireSlotRenderer>
    GetFitSlot(const std::shared_ptr<DiceUtils::Dice> &dice) {
        for (size_t i = 0; i < m_SlotObjects.size(); i++) {
            if (m_SlotObjects[i]->IsFit(dice)) {
                return m_SlotObjects[i];
            }
        }
        return {nullptr};
    }

private:
    void InitImageMap();
    void SetUpTransform(const std::shared_ptr<Cards::Card> &card);
    int m_Size;

    std::vector<std::shared_ptr<RequireSlotRenderer>> m_RequireSlotRenderer;
    const std::shared_ptr<Cards::Card> &m_Card;

    std::shared_ptr<Util::GameObject> m_NameObject;
    std::shared_ptr<Util::GameObject> m_DescriptionObject;
    std::vector<std::shared_ptr<UI::CardsRenderer::RequireSlotRenderer>>
        m_SlotObjects;
    static std::unordered_map<Cards::CardColor, std::shared_ptr<Util::Image>>
        m_ImageMap;
    inline static std::vector<glm::vec2> m_NameOffset = {{15, 125}, {15, 200}};
    inline static std::vector<glm::vec2> m_DescriptionOffset = {{15, -80},
                                                                {15, -125}};
    inline static std::vector<glm::vec2> m_SlotOffset = {{5, 15}, {5, 0}};
};
} // namespace UI::CardsRenderer

#endif
