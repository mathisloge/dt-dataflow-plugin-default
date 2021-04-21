#include "array_node.hpp"
#include <dt/df/core/graph_manager.hpp>
namespace dt::df
{
static Slots makeInputs(IGraphManager &graph_manager)
{
    const auto &int_fac = graph_manager.getSlotFactory("IntSlot");
    return Slots{int_fac(graph_manager, SlotType::input, "size", 0, SlotFieldVisibility::without_connection)};
}
static Slots makeOutput(IGraphManager &graph_manager)
{
    const auto &int_fac = graph_manager.getSlotFactory("IntSlot");
    const auto &span_fac = graph_manager.getSlotFactory("SpanSlot");
    return Slots{int_fac(graph_manager, SlotType::output, "size", 0, SlotFieldVisibility::without_connection),
                 span_fac(graph_manager, SlotType::output, "array", 0, SlotFieldVisibility::without_connection)};
}

ArrayNode::ArrayNode(IGraphManager &graph_manager)
    : BaseNode{graph_manager, kKey, kName, makeInputs(graph_manager), makeOutput(graph_manager)}
{
    initSlots();
}

ArrayNode::ArrayNode(IGraphManager &graph_manager, const nlohmann::json &json)
    : BaseNode(graph_manager, json)
{
    initSlots();
}

void ArrayNode::initSlots()
{}

void ArrayNode::calculate()
{}

void ArrayNode::renderCustomContent()
{}

ArrayNode::~ArrayNode()
{}
} // namespace dt::df
