//
// Created by Nekbakht Zabirov on 19.05.2024.
//

#include "Database.h"
#include <iostream>

namespace Marketplace
{
    Database::Database()
    {
        _conn = PQconnectdb(conninfo);

        if (PQstatus(_conn) != CONNECTION_OK)
        {
            std::cerr << "Connection to database failed: " << PQerrorMessage(_conn) << std::endl;
            PQfinish(_conn);
            return;
        }

        std::cout << "Connected to the database!" << std::endl;
    }

    Database::~Database()
    {
        PQfinish(_conn);
        std::cout << "Database disconnected" << std::endl;
    }

    bool Database::insert(const char* sql, const char* const* params, std::string& result) const
    {
        bool data = false;

        PGresult* res = PQexecParams(_conn,
                                     sql,
                                     5,
                                     nullptr,
                                     params,
                                     nullptr,
                                     nullptr,
                                     0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            data = false;
        }

        if (PQntuples(res) == 1)
        {
            result = PQgetvalue(res, 0, 0);
            data = true;
        }
        else
        {
            data = false;
        }

        PQclear(res);

        return data;
    }

    bool Database::insert(const char* sql, const char* const* params) const
    {
        bool data = false;

        PGresult* res = PQexecParams(_conn,
                                     sql,
                                     4,
                                     nullptr,
                                     params,
                                     nullptr,
                                     nullptr,
                                     0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            std::cerr << "INSERT command failed: " << PQerrorMessage(_conn) << std::endl;
            data = false;
        } else
        {
            data = true;
        }

        PQclear(res);

        return data;
    }

} // Marketplace
