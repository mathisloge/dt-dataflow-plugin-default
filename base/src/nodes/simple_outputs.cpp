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
    ImGui::SetNextItemWidth(100.f);
    if (ImGui::InputInt("value", &output_val_))
        output_slot_->setValue(output_val_);
}

FloatOutputNode::FloatOutputNode(core::IGraphManager &graph_manager)
    : SimpleOutputNode(graph_manager, std::string{kKey}, "Float Output", kNumberSlotKey)
{}

void FloatOutputNode::renderCustomContent()
{
    ImGui::SetNextItemWidth(100.f);
    if (ImGui::InputFloat("value", &output_val_))
        output_slot_->setValue(output_val_);
}

StringOutputNode::StringOutputNode(core::IGraphManager &graph_manager)
    : SimpleOutputNode(graph_manager, std::string{kKey}, "String Output", kStringSlotKey)
{}

void StringOutputNode::renderCustomContent()
{
    ImGui::SetNextItemWidth(100.f);
    if (ImGui::InputTextMultiline("value", &output_val_))
        output_slot_->setValue(output_val_);
}

FlowOutputNode::FlowOutputNode(core::IGraphManager &graph_manager)
    : BaseNode{graph_manager, std::string{kKey}, std::string{kName}}
{}

void FlowOutputNode::init(core::IGraphManager &graph_manager)
{
    output_slot_ = std::dynamic_pointer_cast<OutputSlotT>(addOutput(graph_manager, "FlowSlot", "output", 0));
}
void FlowOutputNode::evaluate()
{}
void FlowOutputNode::renderCustomContent()
{
    ImGui::Text("Warning:\nThis will run in the ui thread.");
    if (ImGui::Button("Trigger"))
    {
        output_slot_->setValue();
    }
}

FlowOutputNode::~FlowOutputNode()
{}

} // namespace dt::df
