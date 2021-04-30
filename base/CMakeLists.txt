cmake_minimum_required(VERSION 3.15)
project(BasePlugin)

set(SOURCES         
    src/plugin.cpp
    src/slots/flow_slot.cpp
    src/nodes/simple_outputs.cpp
    src/nodes/simple_op.cpp
    src/nodes/simple_ops.cpp
    src/nodes/simple_cmp.cpp
    src/nodes/simple_cmps.cpp
    src/nodes/branch_node.cpp
)
corrade_add_plugin(BasePlugin 
    "${DTDF_PLUGIN_INSTALL_DBG_DIR}"
    "${DTDF_PLUGIN_INSTALL_REL_DIR}"
    BasePlugin.conf 
    ${SOURCES}
)
set_property(TARGET BasePlugin PROPERTY CXX_STANDARD 20)

target_include_directories(
    BasePlugin PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(BasePlugin PRIVATE 
    imgui::imgui
    Corrade::PluginManager
    Magnum::Magnum
    Magnum::GL
    dt::imnodes
    dt::DtDataflowCore
    dt::DtDataflowPlugin
)
