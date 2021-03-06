#pragma once
#include <atomic>
#include <dt/df/core/base_node.hpp>
#include <imgui.h>
namespace dt::df
{
class LedNode final : public BaseNode
{
  public:
    static constexpr const char *kKey = "LedNode";
    static constexpr const char *kName = "Led";

  public:
    LedNode(IGraphManager &graph_manager);
    LedNode(IGraphManager &graph_manager, const nlohmann::json &json);
    void calculate() override;

  private:
    void renderCustomContent() override;
    void toggle();
    void initSlots();
    void setColor(const std::shared_ptr<BaseSlot>& slot, int idx);

  private:
    std::atomic_bool is_on_;
    ImColor color_;
};
} // namespace dt::df
