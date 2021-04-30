#include "simple_ops.hpp"

template <class... Ts>
struct overload : Ts...
{
    using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;
namespace dt::df::op
{
DT_DF_IMPL_SIMPLE_OP_BEGIN(Division, division, dividend, divisor, result)
return std::visit(overload{[](float ta, float tb) {
                               return NumberT{(std::abs(tb) < std::numeric_limits<float>::epsilon())
                                                  ? std::numeric_limits<float>::infinity()
                                                  : ta / tb};
                           },
                           [](double ta, double tb) {
                               return NumberT{(std::abs(tb) < std::numeric_limits<double>::epsilon())
                                                  ? std::numeric_limits<double>::infinity()
                                                  : ta / tb};
                           },
                           //! \todo ignore C4804 in this case.
                           [](auto ta, auto tb) { return NumberT{tb > 0 ? ta / tb : 0}; }},
                  a,
                  b);
DT_DF_IMPL_SIMPLE_OP_END

DT_DF_IMPL_SIMPLE_OP_BEGIN(Multiplication, multiply, a, b, result)
return std::visit([](auto ta, auto tb) { return NumberT{ta * tb}; }, a, b);
DT_DF_IMPL_SIMPLE_OP_END

DT_DF_IMPL_SIMPLE_OP_BEGIN(Addition, addition, a, b, result)
return std::visit([](auto ta, auto tb) { return NumberT{ta + tb}; }, a, b);
DT_DF_IMPL_SIMPLE_OP_END

DT_DF_IMPL_SIMPLE_OP_BEGIN(Subtraction, subtraction, a, b, result)
return std::visit([](auto ta, auto tb) { return NumberT{ta - tb}; }, a, b);
DT_DF_IMPL_SIMPLE_OP_END

DT_DF_IMPL_SIMPLE_OP_BEGIN(Modulo, modulo, a, n, result)
return std::visit([](auto ta, auto tb) { return NumberT{std::fmod(ta, tb)}; }, a, b);
DT_DF_IMPL_SIMPLE_OP_END

DT_DF_IMPL_SIMPLE_OP_BEGIN(Pow, power, a, x, result)
return std::visit([](auto ta, auto tb) { return NumberT{std::pow(ta, tb)}; }, a, b);
DT_DF_IMPL_SIMPLE_OP_END
} // namespace dt::df::op
