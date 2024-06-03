//
// Created by Nekbakht Zabirov on 18.05.2024.
//

#include "ProductServiceImpl.h"
#include <iostream>

namespace Marketplace {

    grpc::Status ProductServiceImpl::Upload(grpc::ServerContext* context, const proto::ProductsUploadRequest* request, proto::Response* response) {
        auto items = request->items();

        // Print the received request (for demonstration purposes)
        std::cout << "Received ProductsUploadRequest " << "size = " << items.size() << std::endl;

        for (const auto& item : items)
        {
            std::cout << "Process item with name " << item.name() << std::endl;

            const auto product_entity = new ProductEntity();
            product_entity->barcode = item.barcode();
            product_entity->name = item.name();
            product_entity->description = "";
            product_entity->brand = "";
            product_entity->active = false;

            product_repository->save(*product_entity);

            const auto product_item = new ProductItemEntity();
            product_item->productId = product_entity->id;
            product_item->marketId = "05550bfc-cdbe-45a7-ad8f-f9c7632ae79e";
            product_item->price = item.price();
            product_item->quality = item.quality();

            product_repository->save(*product_item);

            delete product_item;
            delete product_entity;
        }

        response->set_success(true);
        response->set_message("Products uploaded successfully");

        // Return a successful status
        return grpc::Status::OK;
    }

} // namespace Marketplace
