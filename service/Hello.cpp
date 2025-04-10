#include "pch.h"
#include "Hello.h"

using grpc::Status;

// Implementation of the service
HelloServiceImpl::HelloServiceImpl()
{
}

Status HelloServiceImpl::GetHelloMessage(grpc::ServerContext* context, const ::hello::HelloRequest* request, ::hello::HelloReply* reply)
{
	std::cout << "Received: " << request->message() << std::endl;
	reply->set_message("reply from server");
	return Status::OK;
}
