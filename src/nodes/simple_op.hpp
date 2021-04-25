#pragma once
#include <variant>
#include <dt/df/core/base_node.hpp>
#include <dt/df/core/base_slot.hpp>
namespace dt::df::op
{
class SimpleOp : public core::BaseNode
{
  public:
    explicit SimpleOp(core::IGraphManager &graph_manager,
                      const NodeKey &key,
                      const std::string &title,
                      const std::string &in_a_name,
                      const std::string &in_b_name,
                      const std::string &result_name = "result");
    virtual ~SimpleOp();

    void init() override;
    void evaluate() override;

  protected:
    virtual double calc(const double a, const double b) const = 0;

  private:
    void initSlots();
    void setResult(const double res);

  private:
    double in_a_;
    double in_b_;

    using ResultSlotT = core::BaseSlot<const std::variant<bool, int, float, double> &>;
    std::shared_ptr<ResultSlotT> result_slot_;
};
} // namespace dt::df::op
