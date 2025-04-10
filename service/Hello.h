#pragma once

#pragma warning(push)
#pragma warning(disable : 4244) // Example: Disable a specific warning
#pragma warning(disable : 4267) // Disable another specific warning#include <grpcpp/grpcpp.h>
#include <grpcpp/grpcpp.h>
#include "hello.grpc.pb.h"
#pragma warning(pop)            // Restore previous warning settings


using hello::HelloService;

// Implementation of the service
class HelloServiceImpl final : public hello::HelloService::Service
{
	public:
	HelloServiceImpl();
	~HelloServiceImpl() {}

	::grpc::Status GetHelloMessage(grpc::ServerContext* context, const ::hello::HelloRequest* request, ::hello::HelloReply* reply) override;

private:
};
