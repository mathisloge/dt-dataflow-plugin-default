#include <Corrade/PluginManager/AbstractManager.h>
#include <Magnum/Platform/GLContext.h>
#include <dt/df/plugin/helper.hpp>
#include <dt/df/plugin/plugin.hpp>
#include <imnodes.h>
//#include "nodes/array_node.hpp"
#include "nodes/branch_node.hpp"
//#include "nodes/color_node.hpp"
//#include "nodes/led_node.hpp"
#include "nodes/simple_cmps.hpp"
#include "nodes/simple_ops.hpp"
#include "nodes/simple_outputs.hpp"
//#include "nodes/timer_node.hpp"
#include "slots/basic_slots.hpp"
#include "slots/flow_slot.hpp"
namespace dt::df::plugin
{
template <typename TSlot>
void registerSlot(core::IGraphManager &graph)
{
    graph.registerSlotFactory(
        std::string{TSlot::kKey},
        [](core::IGraphManager &graph, SlotType type, const SlotName &name, SlotId local, SlotFieldVisibility vis) {
            return std::make_shared<TSlot>(graph, type, name, local);
        },
        [](const nlohmann::json &json) { return /*std::make_shared<TSlot>(json);*/ nullptr; });
}

class BasePlugin final : public Plugin
{

  public:
    explicit BasePlugin(Corrade::PluginManager::AbstractManager &manager, const std::string &plugin)
        : Plugin{manager, plugin}
    {}

    void setup(Magnum::GL::Context &gl_ctx, ImGuiContext *imgui_ctx, imnodes::Context *imnodes_ctx) override
    {
        Magnum::Platform::GLContext::makeCurrent(&gl_ctx);
        ImGui::SetCurrentContext(imgui_ctx);
        imnodes::SetCurrentContext(imnodes_ctx);
    }
    void registerNodeFactories(core::IGraphManager &graph) override
    {
        registerSimpleOutputNode<IntOutputNode>(graph);
        registerSimpleOutputNode<FloatOutputNode>(graph);
        registerSimpleOutputNode<StringOutputNode>(graph);
        registerSimpleOutputNode<FlowOutputNode>(graph);

        cmp::registerSimpleCmpNode<cmp::EQ>(graph);
        cmp::registerSimpleCmpNode<cmp::GEQ>(graph);
        cmp::registerSimpleCmpNode<cmp::LEQ>(graph);
        cmp::registerSimpleCmpNode<cmp::Greater>(graph);
        cmp::registerSimpleCmpNode<cmp::Less>(graph);
        cmp::registerSimpleCmpNode<cmp::NEQ>(graph);

        op::registerSimpleOpNode<op::Addition>(graph);
        op::registerSimpleOpNode<op::Subtraction>(graph);
        op::registerSimpleOpNode<op::Division>(graph);
        op::registerSimpleOpNode<op::Modulo>(graph);
        op::registerSimpleOpNode<op::Multiplication>(graph);
        op::registerSimpleOpNode<op::Pow>(graph);

        // registerNode<TimerNode>(graph, "utilities/");
        // registerNode<LedNode>(graph, "utilities/");
        // registerNode<ColorNode>(graph, "utilities/");
        registerNode<BranchNode>(graph, "operators/logical/");
        // registerNode<ArrayNode>(graph, "datatype/");
    }
    void registerSlotFactories(core::IGraphManager &graph) override
    {
        registerBaseSlot<NumberSlotT>(graph, std::string{kNumberSlotKey});
        registerBaseSlot<StringSlotT>(graph, std::string{kStringSlotKey});
        registerBaseSlot<ByteArraySlotT>(graph, std::string{kByteArrayKey});
        registerSlot<FlowSlot>(graph);
    }
};
} // namespace dt::df::plugin

CORRADE_PLUGIN_REGISTER(BasePlugin, dt::df::plugin::BasePlugin, "de.mathisloge.dt.dataflow/1.0")
