#pragma once
#include <thread>
#include <boost/asio.hpp>
#include <dt/df/core/base_node.hpp>
#include <dt/df/core/base_slot.hpp>
namespace dt::df
{
class IoCtxNode final : public core::BaseNode
{
  public:
    using IoCtxT = std::shared_ptr<boost::asio::io_context>;
    static constexpr const char *kKey = "IoCtxNode";
    static constexpr const char *kName = "io-context";

  public:
    explicit IoCtxNode(core::IGraphManager &graph_manager);
    void init(core::IGraphManager &graph_manager) override;
    void evaluate() override;
    void onConnect() override;
    void beforeDisconnect() override;
    void shutdown() override;
    ~IoCtxNode();

  private:
    void ioThread();

  private:
    bool run_;
    std::thread io_thread_;
    IoCtxT io_ctx_;
    using OutputT = core::BaseSlot<IoCtxT>;
    std::shared_ptr<OutputT> output_ctx_;
};
} // namespace dt::df
