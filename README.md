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

## 🛠️ How to Build & Test
```bash
mkdir build && cd build
cmake ..
make
./run_tests
```
