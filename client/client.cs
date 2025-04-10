using System;
using System.Threading;
using System.Threading.Tasks;
using Grpc.Core;
using Grpc.Net.Client;
using Hello;

namespace HelloClient
{
    class Program
    {
        static async Task Main(string[] args)
        {
            // Enable insecure HTTP/2 for local development (not recommended for production)
            AppContext.SetSwitch("System.Net.Http.SocketsHttpHandler.Http2UnencryptedSupport", true);
            
            // Create a channel
            using var channel = GrpcChannel.ForAddress("http://localhost:50051");
            
            // Create client
            var client = new HelloService.HelloServiceClient(channel);
            
            // Call the regular RPC
            await CallGetHelloMessageAsync(client);
            
         
            Console.WriteLine("Press any key to exit...");
            Console.ReadKey();
        }
        
        static async Task CallGetHelloMessageAsync(HelloService.HelloServiceClient client)
        {
            try
            {
                // Send a request and get a response
                var request = new HelloRequest { Message = "Hello from client" };
                var reply = await client.GetHelloMessageAsync(request);
                
                Console.WriteLine($"Server response: {reply.Message}");
            }
            catch (RpcException ex)
            {
                Console.WriteLine($"RPC failed: {ex.Status.Detail}");
            }
        }
    }
}
