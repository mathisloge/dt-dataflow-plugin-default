#include "string_slot.hpp"
#include <imgui.h>
#include <imgui_stdlib.h>

namespace dt::df
{

StringSlot::StringSlot(core::IGraphManager &graph_manager,
                       const SlotType type,
                       const SlotName &name,
                       const SlotId local_id)
    : BaseSlot(graph_manager, kKey, type, name, local_id)
{}

} // namespace dt::df
