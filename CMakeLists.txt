cmake_minimum_required(VERSION 3.15)
project(DtDfPluginDefault)

find_package(imgui CONFIG REQUIRED)
find_package(Corrade REQUIRED PluginManager)
find_package(Magnum REQUIRED GL)
find_package(DtDataFlow CONFIG REQUIRED)

set(DTDF_PLUGIN_INSTALL_DBG_DIR "${CMAKE_INSTALL_PREFIX}/bin/dataflow/dbg")
set(DTDF_PLUGIN_INSTALL_REL_DIR "${CMAKE_INSTALL_PREFIX}/bin/dataflow/rel")

set(SOURCES         
    src/plugin.cpp
    src/slots/flow_slot.cpp
    src/nodes/simple_outputs.cpp
    src/nodes/simple_op.cpp
    src/nodes/simple_ops.cpp
    src/nodes/simple_cmp.cpp
    src/nodes/simple_cmps.cpp
    #src/nodes/timer_node.cpp
    #src/nodes/led_node.cpp
    #src/nodes/color_node.cpp
    #src/nodes/branch_node.cpp
    #src/nodes/array_node.cpp
)
message(STATUS "Plugin DBG Install dir: ${DTDF_PLUGIN_INSTALL_DBG_DIR}")
message(STATUS "Plugin REL Install dir: ${DTDF_PLUGIN_INSTALL_REL_DIR}")
corrade_add_plugin(DefaultPlugin 
    "${DTDF_PLUGIN_INSTALL_DBG_DIR}"
    "${DTDF_PLUGIN_INSTALL_REL_DIR}"
    DtDfPluginDefault.conf 
    ${SOURCES}
)
set_property(TARGET DefaultPlugin PROPERTY CXX_STANDARD 20)

target_include_directories(
    DefaultPlugin PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(DefaultPlugin PRIVATE 
    imgui::imgui
    Corrade::PluginManager
    Magnum::Magnum
    Magnum::GL
    dt::imnodes
    dt::DtDataflowCore
    dt::DtDataflowPlugin
)
