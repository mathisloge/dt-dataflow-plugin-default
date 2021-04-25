#pragma once
#include <span>
#include <dt/df/core/base_slot.hpp>
namespace dt::df
{
class SpanSlot final : public core::BaseSlot<const std::span<uint8_t> &>
{
  public:
    static constexpr std::string_view kKey = "SpanSlot";

  public:
    explicit SpanSlot(core::IGraphManager &graph_manager,
                        const SlotType type,
                        const SlotName &name,
                        const SlotId local_id);
};
} // namespace dt::df
