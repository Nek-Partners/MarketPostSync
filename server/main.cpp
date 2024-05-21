#include <ProductRepository.h>
#include <ProductServiceImpl.h>
#include <grpcpp/server_builder.h>

int main(int argc, char* argv[])
{
    grpc::ServerBuilder builder;
    builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());

    Marketplace::ProductServiceImpl my_service;
    builder.RegisterService(&my_service);

    const std::unique_ptr server(builder.BuildAndStart());
    server->Wait();

    return 0;
}
