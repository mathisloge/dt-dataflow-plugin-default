#pragma once
#include <dt/df/core/base_slot.hpp>
namespace dt::df
{
class StringSlot final : public core::BaseSlot<const std::string &>
{
  public:
    static constexpr std::string_view kKey = "StringSlot";

  public:
    explicit StringSlot(core::IGraphManager &graph_manager,
                        const SlotType type,
                        const SlotName &name,
                        const SlotId local_id);
};
} // namespace dt::df
