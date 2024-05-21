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

    void Database::insert(const char* sql, const char* const* params, std::string& result) const
    {
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
            std::cerr << "INSERT command failed: " << PQerrorMessage(_conn) << std::endl;
        }

        if (PQntuples(res) == 1)
        {
            result = PQgetvalue(res, 0, 0);
            std::cout << "Inserted item with result: " << result << std::endl;
        }
        else
        {
            std::cerr << "Error: No id returned." << std::endl;
        }

        PQclear(res);
    }

    void Database::insert(const char* sql, const char* const* params) const
    {
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
            std::cerr << "INSERT command failed: " << PQerrorMessage(_conn) << std::endl;
        }

        PQclear(res);
    }

} // Marketplace
