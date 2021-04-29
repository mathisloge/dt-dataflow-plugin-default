#include <Corrade/PluginManager/AbstractManager.h>
#include <Magnum/Platform/GLContext.h>
#include <dt/df/plugin/helper.hpp>
#include <dt/df/plugin/plugin.hpp>
namespace dt::df::plugin
{

class AsioPlugin final : public Plugin
{

  public:
    explicit AsioPlugin(Corrade::PluginManager::AbstractManager &manager, const std::string &plugin)
        : Plugin{manager, plugin}
    {}

    void setup(Magnum::GL::Context &gl_ctx, ImGuiContext *imgui_ctx, imnodes::Context *imnodes_ctx)
    {
        Magnum::Platform::GLContext::makeCurrent(&gl_ctx);
        ImGui::SetCurrentContext(imgui_ctx);
        imnodes::SetCurrentContext(imnodes_ctx);
    }
    void registerNodeFactories(core::IGraphManager &graph)
    {
    }
    void registerSlotFactories(core::IGraphManager &graph)
    {
    }
};
} // namespace dt::df::plugin

CORRADE_PLUGIN_REGISTER(AsioPlugin, dt::df::plugin::AsioPlugin, "de.mathisloge.dt.dataflow/1.0")
