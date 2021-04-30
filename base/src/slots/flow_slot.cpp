#include "flow_slot.hpp"
namespace dt::df
{

FlowSlot::FlowSlot(core::IGraphManager &graph_manager, const SlotType type, const SlotName &name, const SlotId local_id)
    : FlowBaseSlot(graph_manager, std::string{kKey}, type, name, local_id)
{}

} // namespace dt::df
