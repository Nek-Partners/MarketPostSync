cmake_minimum_required(VERSION 3.22.1)

# Set the CMake policy CMP0068 to NEW
if(POLICY CMP0068)
    cmake_policy(SET CMP0068 NEW)
endif()

project(POSIntegrate)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable RPATH settings
set(CMAKE_BUILD_WITH_INSTALL_NAME_DIR ON)
set(CMAKE_INSTALL_NAME_DIR "@rpath")

# Find necessary packages
find_package(Threads)
find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf REQUIRED)

# Set MySQL directory based on OS
set(MYSQL_DIR ${CMAKE_SOURCE_DIR}/third_party/mysql)

if (WIN32)
    set(MYSQL_INCLUDE_DIR ${MYSQL_DIR}/winx64/include)
    set(MYSQL_LIB "${MYSQL_DIR}/winx64/lib64/vs14/mysqlcppconn-static.lib")
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
        ${Protobuf_INCLUDE_DIRS}
        ${gRPC_INCLUDE_DIRS}
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
        ${Protobuf_LIBRARIES}
)

# Ensure the required directories are included in the project
include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${MYSQL_INCLUDE_DIR}/jdbc
        ${MYSQL_INCLUDE_DIR}/jdbc/cppconn
        ${MYSQL_INCLUDE_DIR}/mysql
)
