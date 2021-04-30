#pragma once
#include <array>
#include <dt/df/core/base_node.hpp>
#include <dt/df/core/flow_base_slot.hpp>
#include <dt/df/core/types.hpp>
#include <imgui.h>
#include "../slots/basic_slots.hpp"
namespace dt::df
{
class BranchNode final : public core::BaseNode
{
  public:
    static constexpr const char *kKey = "BranchNode";
    static constexpr const char *kName = "Branch";

  public:
    explicit BranchNode(core::IGraphManager &graph_manager);
    void init(core::IGraphManager &graph_manager) override;

  private:
    void evaluate() override;
    void setOutput(const bool result);

  private:
    SlotFlowPtr true_out_flow_;
    SlotFlowPtr false_out_flow_;
    bool input_cond_;
};
} // namespace dt::df
