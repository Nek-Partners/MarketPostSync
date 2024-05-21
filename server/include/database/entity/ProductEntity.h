//
// Created by Nekbakht Zabirov on 19.05.2024.
//

#ifndef PRODUCTENTITY_H
#define PRODUCTENTITY_H

#include <string>

namespace Marketplace
{
    struct ProductEntity
    {
        std::string id;
        std::string barcode;
        std::string name;
        std::string description;
        std::string brand;
        bool active;
    };
}

#endif //PRODUCTENTITY_H
