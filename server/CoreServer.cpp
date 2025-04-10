#include "pch.h"
#include "CoreServer.h"

#pragma warning(push)
#pragma warning(disable : 4244) // Example: Disable a specific warning
#pragma warning(disable : 4267) // Disable another specific warning#include <grpcpp/grpcpp.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp\impl\service_type.h>
#pragma warning(pop)            // Restore previous warning settings


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;

CoreServer::CoreServer(const std::string& server_address) noexcept 
	: server_address_(server_address)
	, shutdown_event_(false)
	, server_running_(false)
{
}

// Start the server in a separate thread
bool CoreServer::Start(std::vector<grpc::Service*> services)
{
	if (server_running_)
	{
		std::cout << "Server is already running" << std::endl;
		return false;
	}

	// Build and start the server
	ServerBuilder builder;
	builder.AddListeningPort(server_address_, grpc::InsecureServerCredentials());
	for (auto service : services)
	{
		builder.RegisterService(service);
	}

	server_ = builder.BuildAndStart();
	if (! server_)
	{
		std::cerr << "Failed to start server on " << server_address_ << std::endl;
		return false;
	}

	std::cout << "Server listening on " << server_address_ << std::endl;

	// Start server thread
	server_running_ = true;
	server_thread_  = std::thread(&CoreServer::RunServer, this);

	return true;
}

// Request server to shut down
void CoreServer::RequestShutdown()
{
	if (! server_running_)
	{
		std::cout << "Server is not running" << std::endl;
		return;
	}

	std::cout << "Requesting server shutdown..." << std::endl;

	// Set shutdown event and notify wait thread
	{
		std::unique_lock<std::mutex> lock(shutdown_mutex_);
		shutdown_event_ = true;
		shutdown_cv_.notify_all();
	}
}

// Wait for server to complete shutdown
void CoreServer::WaitForShutdown()
{
	if (server_thread_.joinable())
	{
		server_thread_.join();
	}
	std::cout << "Server fully shut down" << std::endl;
}

// Server thread function
void CoreServer::RunServer()
{
	std::cout << "Server thread started" << std::endl;

	// Wait for shutdown event
	{
		std::unique_lock<std::mutex> lock(shutdown_mutex_);
		shutdown_cv_.wait(lock, [this] { return shutdown_event_; });
	}

	// Shutdown requested
	std::cout << "Shutting down server..." << std::endl;

	// Stop accepting new requests and wait for existing ones to complete
	server_->Shutdown();

	// Server is fully shut down
	server_running_ = false;
	std::cout << "Server shutdown completed" << std::endl;
}
