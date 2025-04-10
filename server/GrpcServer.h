#pragma once
#include <iostream>
#include <vector>
#include <memory>

#ifdef SERVER_EXPORTS
#define SERVER_API __declspec(dllexport)
#else
#define SERVER_API __declspec(dllimport)
#endif

namespace grpc
{
	class Service;
}

class CoreServer;

class SERVER_API GrpcServer
{
public:
	GrpcServer(const std::string& server_address = "0.0.0.0:50051") noexcept;
	~GrpcServer();

	GrpcServer(const GrpcServer&)            = delete;
	GrpcServer& operator=(const GrpcServer&) = delete;
	GrpcServer(GrpcServer&&)                 = delete;
	GrpcServer& operator=(GrpcServer&&)      = delete;

	void startServer();
	void stopServer();
	// service must live in the caller's scope
	void addService(grpc::Service* service);

private:

	std::unique_ptr<CoreServer> server_;
	std::vector<grpc::Service*> services_;
};
