//
// Created by Nekbakht Zabirov on 21.05.2024.
//

#include "Database.h"
#include <cppconn/statement.h>

namespace Marketplace
{
    std::vector<ProductEntity> Database::findAll() const
    {
        std::vector<ProductEntity> result;

        // Create a statement
        sql::Statement* stmt = con->createStatement();

        stmt->execute("SET NAMES 'utf8'");

        // Execute the query
        sql::ResultSet* res = stmt->executeQuery("SELECT barcode, name, price FROM products");

        while (res->next()) {
            const std::string barcode = res->getString("barcode");
            const std::string name = res->getString("name");
            const long double price = res->getDouble("price");

            ProductEntity product_entity;
            product_entity.barcode = barcode;
            product_entity.name = name;
            product_entity.price = static_cast<float>(price);

            result.push_back(product_entity);
        }

        delete res;
        delete stmt;

        return result;
    }
}
