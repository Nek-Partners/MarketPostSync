# Find necessary packages
find_package(Threads)
find_package(gRPC CONFIG REQUIRED)

# Set MySQL directory based on OS
set(MYSQL_DIR ${CMAKE_SOURCE_DIR}/third_party/mysql)

if (WIN32)
    set(MYSQL_INCLUDE_DIR ${MYSQL_DIR}/winx64/include)
    set(MYSQL_LIB
            "${MYSQL_DIR}/winx64/lib64/vs14/mysqlcppconn-static.lib"
            "${MYSQL_DIR}/winx64/lib64/mysqlcppconn-9-vs14.dll"
    )
elseif (APPLE)
    set(MYSQL_INCLUDE_DIR ${MYSQL_DIR}/macos-arm64/include)
    set(MYSQL_LIB "${MYSQL_DIR}/macos-arm64/lib64/libmysqlcppconn-static.a")
else ()
    message(FATAL_ERROR "Unsupported operating system")
endif ()

# Include directories
include_directories(
        include/database
        include/database/entity
        ${MYSQL_INCLUDE_DIR}
)

# Add the executable
add_executable(client
        main.cpp
        src/Database.cpp
)

# Link libraries
target_link_libraries(client
        PRIVATE
        myproto
        ${MYSQL_LIB}
        gRPC::grpc
        gRPC::grpc++
)

# Ensure the required directories are included in the project
include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${MYSQL_INCLUDE_DIR}/jdbc
        ${MYSQL_INCLUDE_DIR}/jdbc/cppconn
        ${MYSQL_INCLUDE_DIR}/mysql
)