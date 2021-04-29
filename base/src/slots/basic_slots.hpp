#pragma once
#include <span>
#include <string>
#include <string_view>
#include <variant>
namespace dt::df
{
using NumberSlotT = const std::variant<bool, int, float, double> &;
constexpr std::string_view kNumberSlotKey = "NumberSlot";

using StringSlotT = const std::string &;
constexpr std::string_view kStringSlotKey = "StringSlot";

using ByteArraySlotT = std::span<uint8_t>;
constexpr std::string_view kByteArrayKey = "ByteArraySlot";

} // namespace dt::df
