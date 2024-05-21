//
// Created by Nekbakht Zabirov on 18.05.2024.
//

#ifndef PRODUCTSERVICE_H
#define PRODUCTSERVICE_H

#include <myproto/product.service.grpc.pb.h>
#include "ProductRepository.h"

namespace Marketplace
{
    class ProductServiceImpl final : public proto::ProductService::Service
    {
    private:
        ProductRepository* product_repository = new ProductRepository();

    public:
        ~ProductServiceImpl() override
        {
            delete product_repository;
        }

        grpc::Status Upload(grpc::ServerContext* context, const proto::ProductsUploadRequest* request,
                            proto::Response* response) override;
    };
} // Marketplace

#endif //PRODUCTSERVICE_H
