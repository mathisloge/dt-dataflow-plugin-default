#pragma once
#include <dt/df/core/base_node.hpp>

#define DT_DF_BUILD_SIMPLE_O_NODE(NODE_NAME)                                                                           \
    class NODE_NAME final : public BaseNode                                                                            \
    {                                                                                                                  \
      public:                                                                                                          \
        static constexpr std::string_view kKey = #NODE_NAME;                                                           \
        NODE_NAME(IGraphManager &graph_manager);                                                                       \
        NODE_NAME(IGraphManager &graph_manager, const nlohmann::json &json);                                           \
        void calculate() override;                                                                                     \
    };

#define DT_DF_BUILD_SIMPLE_O_NODE_IMPL(NODE_NAME, NODE_DISP, SLOT_KEY, SLOT_TITLE)                                     \
    NODE_NAME::##NODE_NAME(IGraphManager &graph_manager)                                                               \
        : BaseNode(graph_manager,                                                                                      \
                   std::string{kKey},                                                                                  \
                   #NODE_DISP,                                                                                         \
                   Slots{},                                                                                            \
                   getOutputs(graph_manager, #SLOT_KEY, #SLOT_TITLE))                                                  \
    {}                                                                                                                 \
                                                                                                                       \
    NODE_NAME::##NODE_NAME(IGraphManager &graph_manager, const nlohmann::json &json)                                   \
        : BaseNode{graph_manager, json}                                                                                \
    {}                                                                                                                 \
    void NODE_NAME::calculate()                                                                                        \
    {                                                                                                                  \
        outputByLocalId(0)->subscribe([this](const BaseSlot *) { calculateIfNoFlow(); });                              \
    }
