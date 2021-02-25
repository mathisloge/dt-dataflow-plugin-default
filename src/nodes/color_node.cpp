#include "color_node.hpp"
#include <dt/df/core/graph_manager.hpp>
#include <dt/df/core/value_less_slot.hpp>
namespace dt::df
{
static Slots createInputs(IGraphManager &graph_manager);
static Slots createOutputs(IGraphManager &graph_manager);
ColorNode::ColorNode(IGraphManager &graph_manager)
    : BaseNode{graph_manager, kKey, kName, createInputs(graph_manager), createOutputs(graph_manager)}
{
    initSlots();
}
ColorNode::ColorNode(IGraphManager &graph_manager, const nlohmann::json &json)
    : BaseNode{graph_manager, json}
{
    initSlots();
}

void ColorNode::renderCustomContent()
{
    ImGui::PushID(this);
    ImGui::SetNextItemWidth(250.f);
    if (ImGui::ColorEdit4("color", &color_[0], ImGuiColorEditFlags__OptionsDefault))
    {
        pushColors();
    }
    ImGui::PopID();
}

void ColorNode::initSlots()
{
    color_.fill(0.f);
    r_ = std::dynamic_pointer_cast<NumberSlot>(outputByLocalId(0));
    g_ = std::dynamic_pointer_cast<NumberSlot>(outputByLocalId(1));
    b_ = std::dynamic_pointer_cast<NumberSlot>(outputByLocalId(2));
    a_ = std::dynamic_pointer_cast<NumberSlot>(outputByLocalId(3));
}

void ColorNode::pushColors()
{
    r_->setValue(color_[0] * 255);
    g_->setValue(color_[1] * 255);
    b_->setValue(color_[2] * 255);
    a_->setValue(color_[3] * 255);
}

Slots createInputs(IGraphManager &graph_manager)
{
    return Slots{};
}

Slots createOutputs(IGraphManager &graph_manager)
{
    Slots slots;
    try
    {
        const auto nb_slot_fac = graph_manager.getSlotFactory("IntSlot");
        slots.emplace_back(nb_slot_fac(graph_manager, SlotType::output, "r", 0, SlotFieldVisibility::never));
        slots.emplace_back(nb_slot_fac(graph_manager, SlotType::output, "g", 1, SlotFieldVisibility::never));
        slots.emplace_back(nb_slot_fac(graph_manager, SlotType::output, "b", 2, SlotFieldVisibility::never));
        slots.emplace_back(nb_slot_fac(graph_manager, SlotType::output, "a", 3, SlotFieldVisibility::never));
    }
    catch (...)
    {}
    return slots;
}
} // namespace dt::df
