find_package(Threads)
find_package(gRPC CONFIG REQUIRED)

add_executable(client
        main.cpp
        src/Database.cpp
)

set(MYSQL_DIR ${CMAKE_SOURCE_DIR}/third_party/mysql)
set(MYSQL_INCLUDE_DIR ${MYSQL_DIR}/macos-arm64/include)

if (WIN32)
    set(MYSQL_INCLUDE_DIR ${MYSQL_DIR}/macos-arm64/include)
elseif (APPLE)
    set(MYSQL_INCLUDE_DIR ${MYSQL_DIR}/winx64/include)
else ()
    message(FATAL_ERROR "Unsupported operating system")
endif ()

if (WIN32)
    set(MYSQL_LIB "${MYSQL_DIR}/winx64/lib64/vs14/mysqlcppconn-static.lib")
elseif (APPLE)
    set(MYSQL_LIB "${MYSQL_DIR}/macos-arm64/lib64/libmysqlcppconn-static.a")
else ()
    message(FATAL_ERROR "Unsupported operating system")
endif ()

include_directories(
        include/database
        include/database/entity
        ${MYSQL_INCLUDE_DIR}/jdbc
        ${MYSQL_INCLUDE_DIR}/jdbc/cppconn
        ${MYSQL_INCLUDE_DIR}/mysql
)

target_link_libraries(client
        PRIVATE
        myproto
        ${MYSQL_LIB}
        gRPC::grpc
        gRPC::grpc++
)