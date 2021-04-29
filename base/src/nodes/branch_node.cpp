#include "branch_node.hpp"
#include <dt/df/core/base_slot.hpp>
namespace dt::df
{
BranchNode::BranchNode(core::IGraphManager &graph_manager)
    : BaseNode{graph_manager, kKey, kName}
    , input_cond_{false}
{}

void BranchNode::init(core::IGraphManager &graph_manager)
{
    addInputFlow(graph_manager);

    true_out_flow_ = std::static_pointer_cast<core::FlowBaseSlot>(addOutput(graph_manager, "FlowSlot", "true", 0));
    false_out_flow_ = std::static_pointer_cast<core::FlowBaseSlot>(addOutput(graph_manager, "FlowSlot", "false", 1));
    std::static_pointer_cast<core::BaseSlot<NumberSlotT>>(addInput(graph_manager, kNumberSlotKey, "condition", 0))
        ->connectToNodeFnc(
            [this](auto number) { std::visit([this](auto expr) { input_cond_ = static_cast<bool>(expr); }, number); });
}

void BranchNode::evaluate()
{
    if (input_cond_)
        true_out_flow_->setValue();
    else
        false_out_flow_->setValue();
}
} // namespace dt::df
