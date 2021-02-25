#pragma once
#include <array>
#include <dt/df/core/base_node.hpp>
#include <dt/df/core/number_slot.hpp>
#include <imgui.h>
namespace dt::df
{
class ColorNode final : public BaseNode
{
  public:
    static constexpr const char *kKey = "ColorNode";
    static constexpr const char *kName = "Color";

  public:
    ColorNode(IGraphManager &graph_manager);
    ColorNode(IGraphManager &graph_manager, const nlohmann::json &json);

  private:
    void renderCustomContent() override;
    void initSlots();
    void pushColors();

  private:
    std::array<float, 4> color_;
    std::shared_ptr<NumberSlot> r_;
    std::shared_ptr<NumberSlot> g_;
    std::shared_ptr<NumberSlot> b_;
    std::shared_ptr<NumberSlot> a_;
};
} // namespace dt::df
