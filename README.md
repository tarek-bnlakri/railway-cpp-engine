# Railway Search Engine (C++ / gRPC)

This is a high-performance C++ microservice built to handle shortest-path Graph traversal for a Railway Reservation System. It is designed to act as a backend engine that receives binary protobuf requests from a Node.js API gateway.

## 🏗️ Architecture
- **Language:** C++17
- **Networking:** gRPC / Protocol Buffers
- **Build System:** CMake
- **Testing:** Google Test (gtest)

## 🚀 Current Status
- [x] Graph Data Structures (`unordered_map` Adjacency List)
- [x] Dijkstra's Algorithm (Min-Heap `std::priority_queue`)
- [x] Automated Unit Tests (gtest)
- [ ] gRPC Server Integration (WIP)
- [ ] CI/CD Pipeline (WIP)

## 🛠️ How to Build & Test (Local)
```bash
mkdir build && cd build
cmake ..
make
./run_tests
```

## 🐳 How to Run (Docker)
The engine is containerized for easy integration with your API Gateway across any OS.
```bash
# Pull and run the server locally on port 50051
docker run -d -p 50051:50051 tarekbenl/railway-cpp-engine:latest
```
