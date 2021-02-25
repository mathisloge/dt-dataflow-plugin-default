#pragma once
#include <dt/df/core/any_slot.hpp>
namespace dt::df
{
class AnySlotImpl final : public AnySlot
{
  public:
    static constexpr std::string_view kKey = "AnySlot";

  public:
    using AnySlot::AnySlot;
    const std::any &anyValue() const override;
    ~AnySlotImpl() = default;

  private:
    void accept(const std::any &value) override;
    bool renderField() override;
    void renderValue() override;

  private:
    std::any any_value_;
};
} // namespace dt::df
