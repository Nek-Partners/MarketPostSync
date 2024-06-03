//
// Created by Nekbakht Zabirov on 19.05.2024.
//

#ifndef DATABASE_H
#define DATABASE_H

#include "ProductEntity.h"
#include <libpq-fe.h>

namespace Marketplace
{
    constexpr auto conninfo = "dbname=kk_market user=kk_market password=u3d0uQ4yMB4KNxX6Q8RxY hostaddr=127.0.0.1 port=5432";

    class Database
    {
    public:
        static Database& getInstance()
        {
            static Database instance;
            return instance;
        }

        Database(const Database&) = delete;
        Database& operator=(const Database&) = delete;

        bool insert(const char* sql, const char* const* params, std::string& result) const;

        bool insert(const char* sql, const char* const* params) const;

    private:
        PGconn* _conn;

        Database();
        ~Database();
    };
} // Marketplace

#endif //DATABASE_H
