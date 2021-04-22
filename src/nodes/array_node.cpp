#include "array_node.hpp"
#include <dt/df/core/base_slot.hpp>
#include <dt/df/core/graph_manager.hpp>
#include <dt/df/core/number_slot.hpp>

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
                 span_fac(graph_manager, SlotType::output, "array", 1, SlotFieldVisibility::without_connection)};
}

ArrayNode::ArrayNode(IGraphManager &graph_manager)
    : BaseNode{graph_manager, kKey, kName, makeInputs(graph_manager), makeOutput(graph_manager)}
    , target_size_{0}
{
    initSlots();
}

ArrayNode::ArrayNode(IGraphManager &graph_manager, const nlohmann::json &json)
    : BaseNode(graph_manager, json)
    , target_size_{0}
{
    initSlots();
}

void ArrayNode::initSlots()
{
    inputByLocalId(0)->subscribe([this](const BaseSlot *slot) {
        auto in_slot = static_cast<const NumberSlot *>(slot);
        if (in_slot->value() < 0)
            return;
        target_size_ = static_cast<size_t>(in_slot->value());

        calculateIfNoFlow();
    });

    out_slot_ = std::dynamic_pointer_cast<SpanSlot>(outputByLocalId(1));
}

void ArrayNode::calculate()
{
    if (target_size_ != 0 && target_size_ != value_.size())
    {
        value_.resize(target_size_);
    }

    out_slot_->setValue(std::span<uint8_t>{value_});
}

void ArrayNode::renderCustomContent()
{}

ArrayNode::~ArrayNode()
{}
} // namespace dt::df
