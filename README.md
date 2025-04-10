### gRPC C++ server and service in two different dlls

When the server and the service are both declared and instatiated in the same dll, the program server is working with the client.
In this case, the service is in a different dll than the service: calling the GetHello() causes

Unhandled exception thrown: read access violation.
closure_list was 0x8
on the server side.
