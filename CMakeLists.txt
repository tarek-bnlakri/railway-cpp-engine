cmake_minimum_required(VERSION 3.15)
project(RailwayEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- PART 1: gRPC Networking ---
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

add_library(route_search_proto ${PROTO_SRC} ${PROTO_HDR} ${GRPC_SRC} ${GRPC_HDR})
target_link_libraries(route_search_proto PUBLIC protobuf::libprotobuf -lgrpc++)


# --- PART 2: Core Graph Engine & Unit Tests ---

# 1. Compile our Graph code into a library
add_library(graph_engine src/graph.cpp src/dijkstra.cpp)

# 2. Tell CMake to automatically download Google Test (gtest)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# 3. Create our Testing Executable
add_executable(run_tests tests/graph_test.cpp)

# 4. Link our tests to our Graph code and to Google Test
target_link_libraries(run_tests PUBLIC graph_engine gtest_main)
