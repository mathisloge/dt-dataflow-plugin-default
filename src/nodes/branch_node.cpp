#include "branch_node.hpp"
#include <dt/df/core/graph_manager.hpp>
#include <dt/df/core/number_slot.hpp>
namespace dt::df
{
static Slots createInputs(IGraphManager &graph_manager);
static Slots createOutputs(IGraphManager &graph_manager);
BranchNode::BranchNode(IGraphManager &graph_manager)
    : BaseNode{graph_manager, kKey, kName, createInputs(graph_manager), createOutputs(graph_manager)}
{
    initSlots();
}
BranchNode::BranchNode(IGraphManager &graph_manager, const nlohmann::json &json)
    : BaseNode{graph_manager, json}
{
    initSlots();
}

void BranchNode::initSlots()
{
    result_ = std::dynamic_pointer_cast<AnySlot>(outputByLocalId(0));
    input_expr_ = std::dynamic_pointer_cast<NumberSlot>(inputByLocalId(0));
    input_if_ = std::dynamic_pointer_cast<AnySlot>(inputByLocalId(1));
    input_else_ = std::dynamic_pointer_cast<AnySlot>(inputByLocalId(2));
    input_expr_->subscribe([this](auto) { setOutput(static_cast<bool>(input_expr_->value())); });
    input_if_->subscribe([this](auto) {
        const bool expr = static_cast<bool>(input_expr_->value());
        if (expr)
            setOutput(expr);
    });
    input_else_->subscribe([this](auto) {
        const bool expr = static_cast<bool>(input_expr_->value());
        if (!expr)
            setOutput(expr);
    });
}

void BranchNode::setOutput(const bool result)
{
    if (result)
        result_->setValue(input_if_->anyValue());
    else
        result_->setValue(input_else_->anyValue());
}

Slots createInputs(IGraphManager &graph_manager)
{
    Slots slots;
    try
    {
        const auto any_slot_fac = graph_manager.getSlotFactory("AnySlot");
        const auto bool_slot_fac = graph_manager.getSlotFactory("BoolSlot");
        slots.emplace_back(bool_slot_fac(graph_manager, SlotType::output, "expr", 0, SlotFieldVisibility::without_connection));
        slots.emplace_back(any_slot_fac(graph_manager, SlotType::output, "if", 1, SlotFieldVisibility::without_connection));
        slots.emplace_back(any_slot_fac(graph_manager, SlotType::output, "else", 2, SlotFieldVisibility::without_connection));
    }
    catch (...)
    {}
    return slots;
}

Slots createOutputs(IGraphManager &graph_manager)
{
    Slots slots;
    try
    {
        const auto any_slot_fac = graph_manager.getSlotFactory("AnySlot");
        slots.emplace_back(any_slot_fac(graph_manager, SlotType::output, "result", 0, SlotFieldVisibility::never));
    }
    catch (...)
    {}
    return slots;
}
} // namespace dt::df
