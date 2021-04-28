#pragma once
#include <variant>
#include <dt/df/core/base_node.hpp>
#include <dt/df/core/base_slot.hpp>
#include <dt/df/core/flow_base_slot.hpp>

namespace dt::df::cmp
{
class SimpleCmp : public core::BaseNode
{
  protected:
    using NumberT = std::variant<bool, int, float, double>;
    using ResultSlotT = core::BaseSlot<const NumberT &>;
    using FlowSlotT = core::FlowBaseSlot;

  public:
    SimpleCmp(core::IGraphManager &graph_manager,
              const NodeKey &key,
              const std::string &title,
              const std::string &in_a_name,
              const std::string &in_b_name,
              const std::string &result_name);
    // SimpleCmp(IGraphManager &graph_manager, const nlohmann::json &json);
    virtual ~SimpleCmp();
    void init(core::IGraphManager &graph_manager) override;
    void evaluate() override;

  protected:
    virtual bool cmp(const NumberT &a, const NumberT &b) const = 0;

  private:
    void initSlots();
    void setResult(const bool res);

  private:
    const std::string in_a_name_;
    const std::string in_b_name_;
    const std::string result_name_;

    NumberT in_a_;
    NumberT in_b_;
    bool result_;

    std::shared_ptr<ResultSlotT> result_slot_;
    std::shared_ptr<FlowSlotT> true_slot_;
    std::shared_ptr<FlowSlotT> false_slot_;
};
} // namespace dt::df::cmp
