#include "simple_outputs.hpp"
#include <imgui.h>
#include <imgui_stdlib.h>
namespace dt::df
{
IntOutputNode::IntOutputNode(core::IGraphManager &graph_manager)
    : SimpleOutputNode(graph_manager, std::string{kKey}, "Int Output", kNumberSlotKey)
{}

void IntOutputNode::renderCustomContent()
{
    if (ImGui::InputInt("value", &output_val_))
        output_slot_->setValue(output_val_);
}

FloatOutputNode::FloatOutputNode(core::IGraphManager &graph_manager)
    : SimpleOutputNode(graph_manager, std::string{kKey}, "Float Output", kNumberSlotKey)
{}

void FloatOutputNode::renderCustomContent()
{
    if (ImGui::InputFloat("value", &output_val_))
        output_slot_->setValue(output_val_);
}

StringOutputNode::StringOutputNode(core::IGraphManager &graph_manager)
    : SimpleOutputNode(graph_manager, std::string{kKey}, "String Output", kStringSlotKey)
{}

void StringOutputNode::renderCustomContent()
{
    if (ImGui::InputTextMultiline("value", &output_val_))
        output_slot_->setValue(output_val_);
}
} // namespace dt::df
