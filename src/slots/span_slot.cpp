#include "span_slot.hpp"
namespace dt::df
{

SpanSlot::SpanSlot(core::IGraphManager &graph_manager, const SlotType type, const SlotName &name, const SlotId local_id)
    : BaseSlot(graph_manager, kKey, type, name, local_id)
{}

} // namespace dt::df
