#include "pch.h"
#include "GrpcServer.h"

#include "CoreServer.h"

/// <summary>
/// GRPC Server constructor
/// <param name="server_address"></param>
GrpcServer::GrpcServer(const std::string& server_address) noexcept 
{
	server_ = std::make_unique<CoreServer>(server_address);
}
GrpcServer::~GrpcServer()
{
}

void GrpcServer::startServer() 
{
	if (! server_->Start(services_))
	{
		// TODO
		return;
	}
	return;
}

void GrpcServer::stopServer() 
{
	server_->RequestShutdown();
	server_->WaitForShutdown();
}

void GrpcServer::addService(grpc::Service* service) 
{
	services_.emplace_back(service);
}
