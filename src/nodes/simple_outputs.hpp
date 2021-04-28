#pragma once
#include <dt/df/core/base_node.hpp>
#include <dt/df/core/base_slot.hpp>
#include <dt/df/core/flow_base_slot.hpp>
#include <dt/df/core/graph_manager.hpp>
#include "../slots/basic_slots.hpp"
#include "simple_output_builder.hpp"

namespace dt::df
{
class IntOutputNode final : public SimpleOutputNode<NumberSlotT>
{
  public:
    static constexpr std::string_view kKey = "IntOutputNode";
    static constexpr std::string_view kName = "Int output";
    explicit IntOutputNode(core::IGraphManager &graph_manager);

  private:
    void renderCustomContent() override;

  private:
    int output_val_;
};

class FloatOutputNode final : public SimpleOutputNode<NumberSlotT>
{
  public:
    static constexpr std::string_view kKey = "FloatOutputNode";
    static constexpr std::string_view kName = "Float output";
    explicit FloatOutputNode(core::IGraphManager &graph_manager);

  private:
    void renderCustomContent() override;

  private:
    float output_val_;
};

class StringOutputNode final : public SimpleOutputNode<StringSlotT>
{
  public:
    static constexpr std::string_view kKey = "StringOutputNode";
    static constexpr std::string_view kName = "String output";
    explicit StringOutputNode(core::IGraphManager &graph_manager);

  private:
    void renderCustomContent() override;

  private:
    std::string output_val_;
};

class FlowOutputNode : public core::BaseNode
{
  public:
    static constexpr std::string_view kKey = "FlowOutputNode";
    static constexpr std::string_view kName = "Flow trigger";
    using OutputSlotT = core::FlowBaseSlot;

    explicit FlowOutputNode(core::IGraphManager &graph_manager);
    void init(core::IGraphManager &graph_manager) override;
    void evaluate() override;
    ~FlowOutputNode();

  private:
    void renderCustomContent() override;

  protected:
    std::shared_ptr<OutputSlotT> output_slot_;
};

template <typename TNode>
void registerSimpleOutputNode(core::IGraphManager &graph)
{
    const std::string disp_name{std::string{"output/"} + std::string{TNode::kName}};
    graph.registerNodeFactory(
        std::string{TNode::kKey},
        disp_name,
        [](core::IGraphManager &graph) { return std::make_shared<TNode>(graph); },
        [](core::IGraphManager &graph, const nlohmann::json &json) {
            return nullptr; /*std::make_shared<TNode>(graph, json);*/
        });
}
} // namespace dt::df
