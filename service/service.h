#pragma once

#ifdef SERVICE_EXPORTS
#define SERVICE_API __declspec(dllexport)
#else
#define SERVICE_API __declspec(dllimport)
#endif

namespace grpc
{
	class Service;
}

SERVICE_API ::grpc::Service* my_service() noexcept;
