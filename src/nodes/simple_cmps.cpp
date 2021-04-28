#include "simple_cmps.hpp"
#include <dt/df/core/graph_manager.hpp>
namespace dt::df::cmp
{

template <class... Ts>
struct overload : Ts...
{
    using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;

DT_DF_IMPL_SIMPLE_CMP_BEGIN(Less, less, a, b, result)
return a < b;
DT_DF_IMPL_SIMPLE_CMP_END

DT_DF_IMPL_SIMPLE_CMP_BEGIN(LEQ, leq, a, b, result)
return a <= b;
DT_DF_IMPL_SIMPLE_CMP_END

#pragma warning(push)
#pragma warning(disable:4805)

DT_DF_IMPL_SIMPLE_CMP_BEGIN(EQ, eq, a, b, result)
return std::visit(
    overload{[](float ta, float tb) { return std::abs(ta - tb) < std::numeric_limits<float>::epsilon(); },
             [](double ta, double tb) { return std::abs(ta - tb) < std::numeric_limits<double>::epsilon(); },
             //! \todo this is currently unsafe to compare. however if we ever add more types to the number field. this
             //! would explode. C4805
             [](auto ta, auto tb) { return ta == tb; }},
    a,
    b);
DT_DF_IMPL_SIMPLE_CMP_END

DT_DF_IMPL_SIMPLE_CMP_BEGIN(NEQ, neq, a, b, result)
return std::visit(
    overload{[](float ta, float tb) { return std::abs(ta - tb) >= std::numeric_limits<float>::epsilon(); },
             [](double ta, double tb) { return std::abs(ta - tb) >= std::numeric_limits<double>::epsilon(); },
             //! \todo this is currently unsafe to compare. however if we ever add more types to the number field. this
             //! would explode. C4805
             [](auto ta, auto tb) { return ta != tb; }},
    a,
    b);
DT_DF_IMPL_SIMPLE_CMP_END

#pragma warning(pop)

DT_DF_IMPL_SIMPLE_CMP_BEGIN(GEQ, geq, a, b, result)
return a >= b;
DT_DF_IMPL_SIMPLE_CMP_END

DT_DF_IMPL_SIMPLE_CMP_BEGIN(Greater, greater, a, b, result)
return a > b;
DT_DF_IMPL_SIMPLE_CMP_END
} // namespace dt::df::cmp
