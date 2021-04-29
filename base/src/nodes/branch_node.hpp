#pragma once
#include <array>
#include <dt/df/core/base_node.hpp>
#include <dt/df/core/flow_base_slot.hpp>
#include "../slots/basic_slots.hpp"
#include <imgui.h>
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
    std::shared_ptr<core::FlowBaseSlot> true_out_flow_;
    std::shared_ptr<core::FlowBaseSlot> false_out_flow_;
    bool input_cond_;
};
} // namespace dt::df
