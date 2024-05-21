find_package(Threads)
find_package(gRPC CONFIG REQUIRED)

# Manually specify the paths to MySQL libraries and includes
set(MySQL_INCLUDE_DIR /opt/homebrew/Cellar/mysql/8.3.0_1/include/mysql)
set(MySQL_LIBRARY_DIR /opt/homebrew/Cellar/mysql/8.3.0_1/lib)
set(MySQL_LIBRARIES /opt/homebrew/Cellar/mysql/8.3.0_1/lib/libmysqlclient.a)

include_directories(${MySQL_INCLUDE_DIR})
link_directories(${MySQL_LIBRARY_DIR})

# Add the source files of your project
add_executable(client src/main.cpp)

# Link the mysql-connector-cpp library
target_link_libraries(client
        PRIVATE
        myproto
        ${MySQL_LIBRARIES}
        gRPC::grpc
        gRPC::grpc++
)