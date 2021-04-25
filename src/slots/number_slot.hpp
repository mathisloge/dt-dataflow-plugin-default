#pragma once
#include <variant>
#include <dt/df/core/base_slot.hpp>
namespace dt::df
{
class NumberSlot final : public core::BaseSlot<const std::variant<bool, int, float, double> &>
{
  public:
    static constexpr std::string_view kKey = "NumberSlot";

  public:
    explicit NumberSlot(core::IGraphManager &graph_manager,
                        const SlotType type,
                        const SlotName &name,
                        const SlotId local_id);
};
} // namespace dt::df
