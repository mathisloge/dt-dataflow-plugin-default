#pragma once
#include <variant>
#include <dt/df/core/base_node.hpp>

namespace dt::df
{
template <typename OutputT>
class SimpleOutputNode : public core::BaseNode
{
  public:
    using OutputSlotT = core::BaseSlot<OutputT>;

    explicit SimpleOutputNode(core::IGraphManager &graph_manager,
                              NodeKey node_key,
                              const std::string &title,
                              const SlotKey &output_slot_key)
        : BaseNode{graph_manager, node_key, title}
        , output_slot_key_{output_slot_key}
    {}

    void init(core::IGraphManager &graph_manager) override
    {
        output_slot_ = std::dynamic_pointer_cast<OutputSlotT>(addOutput(graph_manager, output_slot_key_, "output", 0));
    }
    void evaluate() override
    {}

    ~SimpleOutputNode()
    {}

  protected:
    const SlotKey output_slot_key_;
    std::shared_ptr<OutputSlotT> output_slot_;
};

} // namespace dt::df
