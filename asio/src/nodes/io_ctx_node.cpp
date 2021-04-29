#include "io_ctx_node.hpp"

namespace dt::df
{
IoCtxNode::IoCtxNode(core::IGraphManager &graph_manager)
    : BaseNode(graph_manager, kKey, kName)
{}
void IoCtxNode::init(core::IGraphManager &graph_manager)
{
    output_ctx_ = std::static_pointer_cast<OutputT>(addOutput(graph_manager, "AsioIoContext", "io-context", 0));
    output_ctx_->setValue(io_ctx_);

    run_ = true;
    io_thread_ = std::thread{std::bind(&IoCtxNode::ioThread, this)};
}
void IoCtxNode::evaluate()
{}
void IoCtxNode::onConnect()
{
    output_ctx_->setValue(io_ctx_);
}
void IoCtxNode::shutdown()
{
    run_ = false;
    if (io_thread_.joinable())
    {
        io_thread_.join();
    }
}

void IoCtxNode::ioThread()
{
    while (run_)
    {
        io_ctx_.run();
        //! subsequence calls to run without a wait results in high cpu load
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

IoCtxNode::~IoCtxNode()
{
    shutdown();
}

} // namespace dt::df
