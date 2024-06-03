#include <myproto/product.service.grpc.pb.h>
#include <myproto/products.upload.request.pb.h>
#include <myproto/response.pb.h>
#include <grpcpp/create_channel.h>
#include "Database.h"

Marketplace::Database& db = Marketplace::Database::getInstance();

int main(int argc, char* argv[])
{
    // Setup request
    proto::ProductsUploadRequest product_upload_request;
    proto::Response result;

    std::vector<ProductEntity> dbProducts;

    dbProducts = db.findAll();

    for (auto& [barcode, name, price] : dbProducts)
    {
        proto::ProductItem* item = product_upload_request.add_items();
        item->set_barcode(barcode);
        item->set_name(name);
        item->set_price(price);
        item->set_description("");
        item->set_quality(0);
    }

    // Call
    const auto channel = CreateChannel("146.190.24.131:50051", grpc::InsecureChannelCredentials());
    const std::unique_ptr<proto::ProductService::Stub> stub = proto::ProductService::NewStub(channel);

    grpc::ClientContext context;
    grpc::Status status = stub->Upload(&context, product_upload_request, &result);

    // Output result
    std::cout << "I got: " << result.message() << std::endl;

    return 0;
}
