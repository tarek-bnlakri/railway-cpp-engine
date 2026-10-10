# 🏗️ The C4 Architecture Model

The C4 model is the industry standard for visualizing software architecture. It zooms in like Google Maps: starting from a high-level satellite view (Level 1) and zooming down to the specific code modules (Level 3).

## Level 1: System Context Diagram
*The "Satellite View". Shows how your system interacts with the outside world.*

```mermaid
flowchart TD
    classDef person fill:#08427b,color:#fff,stroke:#052e56,stroke-width:2px
    classDef system fill:#1168bd,color:#fff,stroke:#0b4884,stroke-width:2px

    Traveler(("🧑‍💻 Traveler<br>[Person]")):::person
    System["🚂 Railway Reservation System<br>[Software System]"]:::system
    
    Traveler -->|"Searches for routes & books tickets"| System
```

---

## Level 2: Container Diagram
*The "City View". Unboxes your system to show the high-level applications, databases, and microservices.*

```mermaid
flowchart TD
    classDef person fill:#08427b,color:#fff,stroke:#052e56,stroke-width:2px
    classDef container fill:#438dd5,color:#fff,stroke:#2e6295,stroke-width:2px
    classDef database fill:#2b74ba,color:#fff,stroke:#1e5182,stroke-width:2px

    Traveler(("🧑‍💻 Traveler<br>[Person]")):::person
    
    subgraph System ["Railway Reservation System"]
        direction TB
        API["Node.js API Gateway<br>[Container: Express/TS]"]:::container
        Engine["C++ Route Search Engine<br>[Container: Docker/gRPC]"]:::container
        
        DB[("PostgreSQL Database<br>[Container: Postgres]")]:::database
        Cache[("Redis Cache<br>[Container: Redis]")]:::database
    end
    
    Traveler -->|"API Requests (JSON/HTTPS)"| API
    API -->|"Reads/Writes"| Cache
    API -->|"Requests Dijkstra Math (gRPC)"| Engine
    Engine -->|"Loads graph on boot (libpqxx)"| DB
```

---

## Level 3: Component Diagram (Node.js API Gateway)
*The "Street View". Zooms inside a specific container (Node.js) to show its internal file structure and services.*

```mermaid
flowchart TD
    classDef component fill:#85bbf0,color:#000,stroke:#5d82a8,stroke-width:2px
    classDef ext fill:#999999,color:#fff,stroke:#6b6b6b,stroke-width:2px

    subgraph API ["Node.js API Gateway"]
        direction TB
        Controller["Route Search Controller<br>[Component: Express Router]"]:::component
        Service["Route Search Service<br>[Component: TypeScript]"]:::component
        Stub["gRPC Client Stub<br>[Component: @grpc/grpc-js]"]:::component
        
        Controller -->|"Calls findCheapestPath()"| Service
        Service -->|"Invokes RPC on Cache Miss"| Stub
    end
    
    Cache[("Redis Cache")]:::ext
    Engine["C++ Route Search Engine"]:::ext
    
    Service -.->|"Checks cache first"| Cache
    Stub -.->|"Sends Binary PathRequest"| Engine
```
