#pragma warning(push)
#pragma warning(disable : 4244) // Example: Disable a specific warning
#pragma warning(disable : 4267) // Disable another specific warning#include <grpcpp/grpcpp.h>
#include <grpcpp/grpcpp.h>
#pragma warning(pop)            // Restore previous warning settings

#include "Errors.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;

// Server class to manage the gRPC server lifecycle
class CoreServer
{
	public:
	CoreServer(const std::string& server_address = "0.0.0.0:50051") noexcept;
	// Start the server in a separate thread
	bool Start(std::vector<grpc::Service*> services);

	// Request server to shut down
	void RequestShutdown();

	// Wait for server to complete shutdown
	void WaitForShutdown();

	// Check if server is running
	bool IsRunning() const noexcept { return server_running_; }

	std::string server_address() const noexcept { return server_address_; }

	private:
	// Server thread function
	void RunServer();

	std::string             server_address_;
	std::unique_ptr<Server> server_;

	std::thread             server_thread_;
	std::mutex              shutdown_mutex_;
	std::condition_variable shutdown_cv_;
	bool                    shutdown_event_;
	std::atomic<bool>       server_running_;
};
