#include <myproto/product.service.grpc.pb.h>
#include <myproto/products.upload.request.pb.h>
#include <myproto/response.pb.h>
#include <grpcpp/create_channel.h>
#include "Database.h"


int main(int argc, char* argv[])
{
    std::cout << "Satrt" << std::endl;

    const Marketplace::Database& db = Marketplace::Database::getInstance();

    std::cout << "Db connected" << std::endl;

    // Setup request
    proto::ProductsUploadRequest product_upload_request;
    proto::Response result;

    std::vector<ProductEntity> dbProducts = db.findAll();

    std::cout << "Products found" << std::endl;

    for (auto& [barcode, name, price, quality] : dbProducts)
    {
        proto::ProductItem* item = product_upload_request.add_items();
        item->set_barcode(barcode);
        item->set_name(name);
        item->set_price(price);
        item->set_description("");
        item->set_quality(quality);
    }

    // Call
    const auto channel = CreateChannel("146.190.24.131:50051", grpc::InsecureChannelCredentials());
    const std::unique_ptr<proto::ProductService::Stub> stub = proto::ProductService::NewStub(channel);

    grpc::ClientContext context;
    grpc::Status status = stub->Upload(&context, product_upload_request, &result);

    // Output result
    std::cout << "I got: " << result.message() << std::endl;

    system("pause");

    return 0;
}
