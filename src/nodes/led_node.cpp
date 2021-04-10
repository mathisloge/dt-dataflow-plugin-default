#include "led_node.hpp"
#include <dt/df/core/graph_manager.hpp>
#include <dt/df/core/number_slot.hpp>
#include <dt/df/core/value_less_slot.hpp>
namespace dt::df
{
static Slots createInputs(IGraphManager &graph_manager);
LedNode::LedNode(IGraphManager &graph_manager)
    : BaseNode{graph_manager, kKey, kName, createInputs(graph_manager), Slots{}}
    , is_on_{false}
    , color_{0.f, 1.f, 0.f, 1.f}
{
    initSlots();
}
LedNode::LedNode(IGraphManager &graph_manager, const nlohmann::json &json)
    : BaseNode{graph_manager, json}
    , is_on_{false}
    , color_{0.f, 1.f, 0.f, 1.f}
{
    initSlots();
}

void LedNode::calculate()
{
    setColor(inputByLocalId(1), 0);
    setColor(inputByLocalId(2), 1);
    setColor(inputByLocalId(3), 2);
    setColor(inputByLocalId(4), 3);
}

void LedNode::renderCustomContent()
{
    const ImVec2 p = ImGui::GetCursorScreenPos();
    const float size = 36.f;
    ImDrawList *draw_list = ImGui::GetWindowDrawList();
    const auto pos = ImVec2{p.x + size * 0.5f, p.y + size * 0.5f};
    if (is_on_)
        draw_list->AddCircle(pos, size * 0.5f, color_);
    else
        draw_list->AddCircleFilled(pos, size * 0.5f, color_);
    ImGui::Dummy({size, size});
}

void LedNode::toggle()
{
    is_on_ = !is_on_;
}

void LedNode::initSlots()
{
    inputByLocalId(0)->subscribe([this](auto) { toggle(); });
}

void LedNode::setColor(const std::shared_ptr<BaseSlot>& slot, int idx)
{
    auto slot_nb = std::static_pointer_cast<NumberSlot>(slot);
    if (slot_nb)
    {
        const float value = static_cast<float>(slot_nb->value()) / 255.f;
        switch (idx)
        {
        case 0:
            color_.Value.x = value;
            break;
        case 1:
            color_.Value.y = value;
            break;
        case 2:
            color_.Value.z = value;
            break;
        case 3:
            color_.Value.w = value;
            break;
        }
    }
}

Slots createInputs(IGraphManager &graph_manager)
{
    try
    {
        const auto &trigger_slot_fac = graph_manager.getSlotFactory("TriggerSlot");
        const auto &int_slot_fac = graph_manager.getSlotFactory("IntSlot");
        return Slots{
            trigger_slot_fac(graph_manager, SlotType::input, "toggle", 0, SlotFieldVisibility::without_connection),
            int_slot_fac(graph_manager, SlotType::input, "r", 1, SlotFieldVisibility::without_connection),
            int_slot_fac(graph_manager, SlotType::input, "g", 2, SlotFieldVisibility::without_connection),
            int_slot_fac(graph_manager, SlotType::input, "b", 3, SlotFieldVisibility::without_connection),
            int_slot_fac(graph_manager, SlotType::input, "a", 4, SlotFieldVisibility::without_connection)};
    }
    catch (...)
    {}
    return Slots{};
}
} // namespace dt::df
