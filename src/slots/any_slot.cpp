#pragma once
#include "any_slot.hpp"
#include <imgui.h>

namespace dt::df
{
const std::any &AnySlotImpl::anyValue() const
{
    return any_value_;
}
void AnySlotImpl::accept(const std::any &value)
{
    any_value_ = value;
}
bool AnySlotImpl::renderField()
{
    ImGui::Text(name().c_str());
    return false;
}
void AnySlotImpl::renderValue()
{}
} // namespace dt::df
