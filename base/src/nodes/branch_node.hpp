#pragma once
#include <array>
#include <dt/df/core/any_slot.hpp>
#include <dt/df/core/base_node.hpp>
#include <dt/df/core/number_slot.hpp>
#include <imgui.h>
namespace dt::df
{
class BranchNode final : public BaseNode
{
  public:
    static constexpr const char *kKey = "BranchNode";
    static constexpr const char *kName = "Branch";

  public:
    BranchNode(IGraphManager &graph_manager);
    BranchNode(IGraphManager &graph_manager, const nlohmann::json &json);

  private:
    void initSlots();
    void calculate() override;
    void setOutput(const bool result);

  private:
    std::shared_ptr<NumberSlot> input_expr_;
    std::shared_ptr<AnySlot> input_if_;
    std::shared_ptr<AnySlot> input_else_;
    std::shared_ptr<AnySlot> result_;
};
} // namespace dt::df
