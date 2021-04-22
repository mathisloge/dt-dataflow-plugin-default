#include "span_slot_impl.hpp"
namespace dt::df
{

SpanSlot::Type SpanSlotImpl::value() const
{
    return value_;
}

void SpanSlotImpl::accept(Type value)
{
    value_ = value;
}

} // namespace dt::df
