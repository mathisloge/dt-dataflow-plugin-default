cmake_minimum_required(VERSION 3.15)
project(AsioPlugin)

set(SOURCES         
    src/plugin.cpp
    src/nodes/io_ctx_node.cpp
)
message(STATUS "Plugin DBG Install dir: ${DTDF_PLUGIN_INSTALL_DBG_DIR}")
message(STATUS "Plugin REL Install dir: ${DTDF_PLUGIN_INSTALL_REL_DIR}")
corrade_add_plugin(AsioPlugin 
    "${DTDF_PLUGIN_INSTALL_DBG_DIR}"
    "${DTDF_PLUGIN_INSTALL_REL_DIR}"
    AsioPlugin.conf 
    ${SOURCES}
)
set_property(TARGET AsioPlugin PROPERTY CXX_STANDARD 20)

target_include_directories(
    AsioPlugin PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(AsioPlugin PRIVATE 
    imgui::imgui
    Corrade::PluginManager
    Magnum::Magnum
    Magnum::GL
    dt::imnodes
    dt::DtDataflowCore
    dt::DtDataflowPlugin
)
