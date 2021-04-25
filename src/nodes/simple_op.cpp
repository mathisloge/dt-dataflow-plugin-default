#include "simple_op.hpp"
#include <dt/df/core/graph_manager.hpp>
namespace dt::df::op
{
#if 0
static Slots makeInputs(IGraphManager &graph_manager, const std::string &in_a_name, const std::string &in_b_name)
{
    const auto &flot_fac = graph_manager.getSlotFactory("FloatingSlot");
    return Slots{flot_fac(graph_manager, SlotType::input, in_a_name, 0, SlotFieldVisibility::without_connection),
                 flot_fac(graph_manager, SlotType::input, in_b_name, 1, SlotFieldVisibility::without_connection)};
}
static Slots makeOutput(IGraphManager &graph_manager, const std::string &out_res_name)
{
    const auto &flot_fac = graph_manager.getSlotFactory("FloatingSlot");
    return Slots{flot_fac(graph_manager, SlotType::output, out_res_name, 0, SlotFieldVisibility::without_connection)};
}
#endif
SimpleOp::SimpleOp(core::IGraphManager &graph_manager,
                   const NodeKey &key,
                   const std::string &title,
                   const std::string &in_a_name,
                   const std::string &in_b_name,
                   const std::string &result_name)
    : BaseNode{graph_manager, key, title}
{}

void SimpleOp::init()
{
    result_slot_ = std::dynamic_pointer_cast<ResultSlotT>(outputByLocalId(0));

    std::dynamic_pointer_cast<ResultSlotT>(inputByLocalId(0))->connectToNodeFnc([this](const auto &number) {
        std::visit([this](auto &&arg) { in_a_ = static_cast<double>(arg); }, number);
    });
    std::dynamic_pointer_cast<ResultSlotT>(inputByLocalId(1))->connectToNodeFnc([this](const auto &number) {
        std::visit([this](auto &&arg) { in_b_ = static_cast<double>(arg); }, number);
    });
}

void SimpleOp::evaluate()
{
    setResult(calc(in_a_, in_b_));
}

void SimpleOp::setResult(const double res)
{
    result_slot_->setValue(res);
}

SimpleOp::~SimpleOp()
{}
} // namespace dt::df::op
