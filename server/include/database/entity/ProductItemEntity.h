//
// Created by Nekbakht Zabirov on 19.05.2024.
//

#ifndef PRODUCTITEMENTITY_H
#define PRODUCTITEMENTITY_H

#include <string>

namespace Marketplace
{
    struct ProductItemEntity
    {
        std::string productId;
        std::string marketId;
        int quality;
        float price;
    };
}

#endif //PRODUCTITEMENTITY_H
