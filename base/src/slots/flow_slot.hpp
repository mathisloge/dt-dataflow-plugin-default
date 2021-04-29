#pragma once
#include <span>
#include <dt/df/core/flow_base_slot.hpp>
namespace dt::df
{
class FlowSlot final : public core::FlowBaseSlot
{
  public:
    static constexpr std::string_view kKey = "FlowSlot";

  public:
    explicit FlowSlot(core::IGraphManager &graph_manager,
                      const SlotType type,
                      const SlotName &name,
                      const SlotId local_id);
};
} // namespace dt::df
