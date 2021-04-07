#pragma once
#include "trigger_slot.hpp"
#include <imgui.h>
namespace dt::df
{

void TriggerSlot::notify()
{
    valueChanged();
}

} // namespace dt::df
