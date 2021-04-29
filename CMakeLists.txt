cmake_minimum_required(VERSION 3.15)
project(DtDfPlugins)

find_package(imgui CONFIG REQUIRED)
find_package(Corrade REQUIRED PluginManager)
find_package(Magnum REQUIRED GL)
find_package(DtDataFlow CONFIG REQUIRED)

set(DTDF_PLUGIN_INSTALL_DBG_DIR "${CMAKE_INSTALL_PREFIX}/bin/dataflow/dbg")
set(DTDF_PLUGIN_INSTALL_REL_DIR "${CMAKE_INSTALL_PREFIX}/bin/dataflow/rel")
message(STATUS "Plugin DBG Install dir: ${DTDF_PLUGIN_INSTALL_DBG_DIR}")
message(STATUS "Plugin REL Install dir: ${DTDF_PLUGIN_INSTALL_REL_DIR}")

add_subdirectory(base)
add_subdirectory(asio)
