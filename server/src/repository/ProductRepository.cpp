//
// Created by Nekbakht Zabirov on 19.05.2024.
//

#include "ProductRepository.h"

namespace Marketplace
{
    bool ProductRepository::save(ProductEntity& entity) const
    {
        const char* params[5];

        params[0] = entity.barcode.c_str();
        params[1] = entity.name.c_str();
        params[2] = entity.description.c_str();
        params[3] = entity.brand.c_str();
        params[4] = std::to_string(entity.active).c_str();

        const auto sql =
            "INSERT INTO product (barcode, name, description, brand, active) VALUES ($1, $2, $3, $4, $5) RETURNING id::text";

        return db.insert(sql, params, entity.id);
    }

    bool ProductRepository::save(const ProductItemEntity& entity) const
    {
        const char* params[4];

        params[0] = entity.productId.c_str();
        params[1] = entity.marketId.c_str();
        params[2] = std::to_string(entity.price).c_str();
        params[3] = std::to_string(entity.quality).c_str();

        const auto sql =
            R"(INSERT INTO product_item ("productId", "marketId", "price", "quality") VALUES ($1, $2, $3, $4))";

        return db.insert(sql, params);
    }

}
