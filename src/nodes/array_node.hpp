#pragma once
#include <vector>
#include <dt/df/core/base_node.hpp>
#include <dt/df/core/span_slot.hpp>
#include <imgui.h>

namespace dt::df
{
class ArrayNode final : public BaseNode
{
  public:
    static constexpr const char *kKey = "ArrayNode";
    static constexpr const char *kName = "Array";

  public:
    ArrayNode(IGraphManager &graph_manager);
    ArrayNode(IGraphManager &graph_manager, const nlohmann::json &json);
    void calculate() override;
    ~ArrayNode();

  private:
    void renderCustomContent() override;
    void initSlots();

  private:
    size_t target_size_;
    std::vector<uint8_t> value_;

    std::shared_ptr<SpanSlot> out_slot_;
};
} // namespace dt::df
