#include "branch_node.hpp"
#include <dt/df/core/base_slot.hpp>
namespace dt::df
{
BranchNode::BranchNode(core::IGraphManager &graph_manager)
    : BaseNode{graph_manager, kKey, kName}
    , input_cond_{false}
    , true_out_flow_{nullptr}
    , false_out_flow_{nullptr}
{}

void BranchNode::init(core::IGraphManager &graph_manager)
{
    addInputFlow(graph_manager);

    std::static_pointer_cast<core::BaseSlot<NumberSlotT>>(addInput(graph_manager, std::string{kNumberSlotKey}, "condition", 0))
        ->connectToNodeFnc(
            [this](auto number) { std::visit([this](auto expr) { input_cond_ = static_cast<bool>(expr); }, number); });

    true_out_flow_ = addCustomOutputFlow(graph_manager, "true", 0);
    false_out_flow_ = addCustomOutputFlow(graph_manager, "false", 1);
}

void BranchNode::evaluate()
{
    if (input_cond_)
        true_out_flow_->setValue();
    else
        false_out_flow_->setValue();
}
} // namespace dt::df
