#include <myproto/products.upload.request.pb.h>
#include <myproto/products.upload.request.grpc.pb.h>
#include <grpcpp/create_channel.h>
#include <myproto/product.service.grpc.pb.h>
#include <myproto/response.pb.h>
#include <mysql/mysql.h>

int main(int argc, char* argv[])
{
    // Setup request
    proto::ProductsUploadRequest product_upload_request;
    proto::Response result;
    proto::ProductItem* item = product_upload_request.add_items();

    // Call
    const auto channel = CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    const std::unique_ptr<proto::ProductService::Stub> stub = proto::ProductService::NewStub(channel);

    grpc::ClientContext context;
    grpc::Status status = stub->Upload(&context, product_upload_request, &result);

    // Output result
    std::cout << "I got:" << std::endl;

    return 0;
}