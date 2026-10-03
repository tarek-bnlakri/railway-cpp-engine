cmake_minimum_required(VERSION 3.15)
project(RailwayEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Protobuf REQUIRED)
find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin)

set(PROTO_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proto/route_search.proto")
set(PROTO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto")

set(PROTO_SRC "${CMAKE_CURRENT_BINARY_DIR}/route_search.pb.cc")
set(PROTO_HDR "${CMAKE_CURRENT_BINARY_DIR}/route_search.pb.h")
set(GRPC_SRC "${CMAKE_CURRENT_BINARY_DIR}/route_search.grpc.pb.cc")
set(GRPC_HDR "${CMAKE_CURRENT_BINARY_DIR}/route_search.grpc.pb.h")

add_custom_command(
      OUTPUT "${PROTO_SRC}" "${PROTO_HDR}" "${GRPC_SRC}" "${GRPC_HDR}"
      COMMAND protobuf::protoc
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
           --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
           -I "${PROTO_DIR}"
           --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
           "${PROTO_FILE}"
      DEPENDS "${PROTO_FILE}")

add_library(route_search_proto
    ${PROTO_SRC}
    ${PROTO_HDR}
    ${GRPC_SRC}
    ${GRPC_HDR})

# Link against the system's protobuf and grpc++ libraries
target_link_libraries(route_search_proto PUBLIC protobuf::libprotobuf -lgrpc++)
