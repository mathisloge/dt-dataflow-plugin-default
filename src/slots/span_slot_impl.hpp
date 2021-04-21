#pragma once
#include <dt/df/core/span_slot.hpp>
namespace dt::df
{
class SpanSlotImpl final : public SpanSlot
{
  public:
    static constexpr std::string_view kKey = "SpanSlot";

  public:
    using SpanSlot::SpanSlot;
    SpanSlot::Type value() const override;
    ~SpanSlotImpl() = default;

  private:
    SpanSlot::Type value_;
};
} // namespace dt::df
