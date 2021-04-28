#include "simple_op.hpp"
#include <dt/df/core/graph_manager.hpp>
namespace dt::df::op
{
SimpleOp::SimpleOp(core::IGraphManager &graph_manager,
                   const NodeKey &key,
                   const std::string &title,
                   const std::string &in_a_name,
                   const std::string &in_b_name,
                   const std::string &result_name)
    : BaseNode{graph_manager, key, title}
    , in_a_name_{in_a_name}
    , in_b_name_{in_b_name}
    , result_name_{result_name}
{}

void SimpleOp::init(core::IGraphManager &graph_manager)
{
    result_slot_ = std::dynamic_pointer_cast<ResultSlotT>(addOutput(graph_manager, "NumberSlot", result_name_, 0));

    std::dynamic_pointer_cast<ResultSlotT>(addInput(graph_manager, "NumberSlot", in_a_name_, 0))
        ->connectToNodeFnc([this](const auto &number) {
            std::visit([this](auto &&arg) { in_a_ = static_cast<double>(arg); }, number);
        });
    std::dynamic_pointer_cast<ResultSlotT>(addInput(graph_manager, "NumberSlot", in_b_name_, 1))
        ->connectToNodeFnc([this](const auto &number) {
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
