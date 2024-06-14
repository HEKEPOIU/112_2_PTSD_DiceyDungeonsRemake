#include "UI/CardsRenderer/CardRenderer.hpp"
#include "Util/Logger.hpp"
#include "Util/Text.hpp"

namespace UI::CardsRenderer {

CardRenderer::CardRenderer(const std::shared_ptr<Cards::Card> &card)
    : m_Size(card->GetSize()),
      m_Card(card) {
    if (m_ImageMap.empty()) {
        InitImageMap();
    }
    SetDrawable(m_ImageMap[card->GetColor()]);
    // this should use 9-slice scale, but it's not supported yet,
    // and I don't know how to implement it.
    // https://blog.simonjaeger.ch/implementing-9-slice-scaling-with-the-canvas-api
    // above link is impl detail, but it seem complicated to impl on pure opengl
    // and sdl2.
    SetUpTransform(m_Card);
    auto onCardUsedFunction = std::bind(&CardRenderer::OnCardUsed, this);
    m_Card->BindOnCardUsedEvent("OnCardUsedUI", onCardUsedFunction);
}

CardRenderer::~CardRenderer() {
    m_Card->UnBindOnCardUsedEvent("OnCardUsedUI");
    // I don't know why it's sometime cause segfault devided by zero??
}

void CardRenderer::InitImageMap() {
    m_ImageMap = {
        {Cards::CardColor::RED,
         std::make_shared<Util::Image>(RESOURCE_DIR
                                       "/graphics/ui/panels/small_red.png")},
        {Cards::CardColor::YELLOW,
         std::make_shared<Util::Image>(RESOURCE_DIR
                                       "/graphics/ui/panels/small_yellow.png")},
        {Cards::CardColor::BLUE,
         std::make_shared<Util::Image>(RESOURCE_DIR
                                       "/graphics/ui/panels/small_blue.png")},
        {Cards::CardColor::GREEN,
         std::make_shared<Util::Image>(RESOURCE_DIR
                                       "/graphics/ui/panels/small_green.png")},
        {Cards::CardColor::GREY,
         std::make_shared<Util::Image>(RESOURCE_DIR
                                       "/graphics/ui/panels/small_grey.png")},
        {Cards::CardColor::ORANGE,
         std::make_shared<Util::Image>(RESOURCE_DIR
                                       "/graphics/ui/panels/small_orange.png")},
        {Cards::CardColor::PINK,
         std::make_shared<Util::Image>(RESOURCE_DIR
                                       "/graphics/ui/panels/small_pink.png")},
        {Cards::CardColor::PURPLE,
         std::make_shared<Util::Image>(
             RESOURCE_DIR "/graphics/ui/panels/small_purple.png")}};
}

void CardRenderer::SetUpTransform(const std::shared_ptr<Cards::Card> &card) {

    m_NameObject = std::make_shared<Util::GameObject>();
    auto nameText = std::make_shared<Util::Text>(
        RESOURCE_DIR "/NotoSans-Regular.ttf", 40, card->GetCardName(),
        Util::Color(255, 255, 255));
    m_NameObject->SetDrawable(nameText);
    m_NameObject->SetZIndex(GetZIndex() + 1);

    m_DescriptionObject = std::make_shared<Util::GameObject>();
    auto descriptionText = std::make_shared<Util::Text>(
        RESOURCE_DIR "/NotoSans-Regular.ttf", 30, card->GetCardDescription(),
        Util::Color(255, 255, 255));
    m_DescriptionObject->SetDrawable(descriptionText);
    m_DescriptionObject->SetZIndex(GetZIndex() + 1);

    auto cardSlot = card->GetRequireSlot();

    for (auto slot : cardSlot) {
        auto slotRenderer = slot->GetRenderer();
        slotRenderer->SetZIndex(GetZIndex() + 1);
        for (auto slotChild : slotRenderer->GetChildren()) {
            slotChild->SetZIndex(GetZIndex() + 2);
        }
        slotRenderer->m_Transform.scale = {.5, .5};
        m_SlotObjects.push_back(slotRenderer);
        AddChild(slotRenderer);
    }

    switch (m_Size) {
    case 2:
        m_Transform.scale = {.5, .8};
        break;
    default:
        m_Transform.scale = {.5, .5};
        break;
    }
    SetTranslate({0, 0});
    AddChild(m_NameObject);
    AddChild(m_DescriptionObject);
}

void CardRenderer::SetTranslate(const glm::vec2 &translate) {
    m_Transform.translation = translate;
    switch (m_Size) {
    case 2:
        m_NameObject->m_Transform.translation = translate + m_NameOffset[1];
        m_DescriptionObject->m_Transform.translation =
            translate + m_DescriptionOffset[1];

        { // this bracket is because of switch statement "break" will jump
          // out of {}, and ignore outside switch.
            int slotNum = m_SlotObjects.size();
            auto slotSize =
                m_SlotObjects[0]
                    ->GetScaledSize(); // we thing slot are same size.
            auto cardCenter = translate + m_SlotOffset[1];
            switch (slotNum) {
            case 1:
                m_SlotObjects[0]->m_Transform.translation = cardCenter;
                for (auto child : m_SlotObjects[0]->GetChildren()) {
                    child->m_Transform.translation = cardCenter;
                }
                break;
            case 2:
                m_SlotObjects[0]->m_Transform.translation =
                    cardCenter - glm::vec2(10 + slotSize.x / 2, 0);
                m_SlotObjects[1]->m_Transform.translation =
                    cardCenter + glm::vec2(10 + slotSize.x / 2, 0);
                for (auto child : m_SlotObjects[1]->GetChildren()) {
                    child->m_Transform.translation =
                        cardCenter + glm::vec2(10 + slotSize.x / 2, 0);
                }
                for (auto child : m_SlotObjects[0]->GetChildren()) {
                    child->m_Transform.translation =
                        cardCenter + glm::vec2(10 + slotSize.x / 2, 0);
                }
                break;
            default:
                throw std::runtime_error("Not Implemented 2 slot Above");
                break;
            }
        }

        break;
    default:
        m_NameObject->m_Transform.translation = translate + m_NameOffset[0];
        m_DescriptionObject->m_Transform.translation =
            translate + m_DescriptionOffset[0];
        for (auto slotObj : m_SlotObjects) {
            slotObj->m_Transform.translation = translate + m_SlotOffset[0];
            for (auto child : slotObj->GetChildren()) {
                child->m_Transform.translation = translate + m_SlotOffset[0];
            }
        }
        break;
    }
}

void CardRenderer::OnCardUsed() {
    SetCardVisible(false);
}

std::unordered_map<Cards::CardColor, std::shared_ptr<Util::Image>>
    CardRenderer::m_ImageMap{};
} // namespace UI::CardsRenderer
