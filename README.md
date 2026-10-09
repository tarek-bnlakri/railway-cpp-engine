# Railway Search Engine (C++ / gRPC)

This is a high-performance C++ microservice built to handle shortest-path Graph traversal for a Railway Reservation System. It is designed to act as a backend engine that receives binary protobuf requests from a Node.js API gateway.

## 🏗️ Systems Architecture

```mermaid
flowchart TD
    %% Define our colors
    classDef client fill:#3498db,stroke:#2980b9,stroke-width:2px,color:#fff;
    classDef nodejs fill:#2ecc71,stroke:#27ae60,stroke-width:2px,color:#fff;
    classDef docker fill:#34495e,stroke:#2c3e50,stroke-width:2px,color:#fff;
    classDef cpp fill:#e74c3c,stroke:#c0392b,stroke-width:2px,color:#fff;
    classDef grpc fill:#f39c12,stroke:#d35400,stroke-width:2px,color:#fff;

    %% Nodes
    User(("🧑‍💻 User / Postman")):::client
    
    subgraph Windows ["🖥️ Windows (Host OS)"]
        NodeJS["Node.js API Gateway\n(Express / TypeScript)"]:::nodejs
    end

    subgraph Docker ["🐳 Docker Container (Linux VM)"]
        direction TB
        gRPC["gRPC Server\n(Listening on Port 50051)"]:::grpc
        Engine["C++ Dijkstra Engine\n(std::priority_queue)"]:::cpp
        Graph["Memory Graph\n(std::unordered_map)"]:::cpp
        
        gRPC -->|Decodes Protobuf Request| Engine
        Engine <-->|Queries Train Edges| Graph
        Engine -->|Returns Cheapest Path| gRPC
    end

    %% Network Flow
    User -->|HTTP GET /api/search?from=London&to=Berlin| NodeJS
    NodeJS ==>|1. Serializes to Binary\n2. Sends over TCP| gRPC
    gRPC ==>|3. Translates C++ struct to JSON\n4. Sends over TCP| NodeJS
    NodeJS -->|HTTP 200 OK (JSON)| User
```

- **Language:** C++17
- **Networking:** gRPC / Protocol Buffers
- **Build System:** CMake
- **Testing:** Google Test (gtest)

## 🚀 Current Status
- [x] Graph Data Structures (`unordered_map` Adjacency List)
- [x] Dijkstra's Algorithm (Min-Heap `std::priority_queue`)
- [x] Automated Unit Tests (gtest)
- [x] gRPC Server Integration
- [x] Docker Containerization
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
