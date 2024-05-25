//
// Created by Nekbakht Zabirov on 21.05.2024.
//

#ifndef DATABASE_H
#define DATABASE_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include "ProductEntity.h"

constexpr auto host = "tcp://127.0.0.1:3306";
constexpr auto user = "root";
constexpr auto password = "your_password";
constexpr auto schema = "your_database";

namespace Marketplace
{
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

        [[nodiscard]] std::vector<ProductEntity> findAll() const;

    private:
        sql::Connection* con;

        Database()
        {
            sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
            con = driver->connect("tcp://127.0.0.1:3306", user, password);
            con->setSchema(schema);
        }

        ~Database()
        {
            con->close();
            delete con;
        }
    };
};

#endif //DATABASE_H
