find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set(PROTO_FILES
        myproto/product.item.proto
        myproto/products.upload.request.proto
        myproto/response.proto
        myproto/product.service.proto
)

add_library(myproto ${PROTO_FILES})
target_link_libraries(myproto
        PRIVATE
        protobuf::libprotobuf
)
target_include_directories(myproto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET myproto LANGUAGE cpp)
protobuf_generate(TARGET myproto LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")