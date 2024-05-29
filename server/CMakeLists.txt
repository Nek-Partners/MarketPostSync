find_package(Threads)
find_package(gRPC REQUIRED)
find_package(PostgreSQL REQUIRED)

include_directories(
        include/service
        include/repository
        include/database
        include/database/entity
)

add_executable(server
        main.cpp
        src/service/ProductServiceImpl.cpp
        src/database/Database.cpp
        src/repository/ProductRepository.cpp
)

target_include_directories(server
        PRIVATE
        ${PostgreSQL_INCLUDE_DIRS}
)

target_link_libraries(server
        PRIVATE
        myproto
        gRPC::grpc
        gRPC::grpc++
        ${PostgreSQL_LIBRARIES}
)

install(TARGETS server
        DESTINATION bin
)