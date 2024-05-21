//
// Created by Nekbakht Zabirov on 19.05.2024.
//

#ifndef PRODUCTREPOSITORY_H
#define PRODUCTREPOSITORY_H
#include <Database.h>
#include <ProductEntity.h>
#include <ProductItemEntity.h>

namespace Marketplace
{
    class ProductRepository
    {
    private:
        Database& db = Database::getInstance();

    public:
        void save(ProductEntity& entity) const;
        void save(const ProductItemEntity& entity) const;
    };
}

#endif //PRODUCTREPOSITORY_H
