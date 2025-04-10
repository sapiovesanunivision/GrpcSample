// server_app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "..\server\GrpcServer.h"
#include  "..\service\service.h"

int main()
{
    GrpcServer server;
    ::grpc::Service* service = my_service();
    server.addService(service);
    server.startServer();
	std::cout << "Server started. Press Enter to stop..." << std::endl;
    std::cin.get();
    server.stopServer();
	std::cout << "Server stopped." << std::endl;
}
