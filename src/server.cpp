#include "server.h"
#include "dijkstra.h"
#include <iostream>

RouteSearchServiceImpl::RouteSearchServiceImpl() {
    // In an enterprise app, this would be fetched from PostgreSQL/Redis on startup.
    // For now, let's load a hardcoded graph into memory when the server boots.
    std::cout << "[Server] Loading Railway Graph Data into Memory..." << std::endl;
    railway_graph.addEdge("London", "Paris", 150.0, "ROUTE_001");
    railway_graph.addEdge("Paris", "Berlin", 100.0, "ROUTE_002");
    railway_graph.addEdge("London", "Berlin", 300.0, "ROUTE_003");
    std::cout << "[Server] Graph Data Loaded! Ready for requests." << std::endl;
}

grpc::Status RouteSearchServiceImpl::FindCheapestPath(
    grpc::ServerContext* context, 
    const PathRequest* request, 
    PathResponse* response) 
{
    std::cout << "[Server] Received Search Request: " << request->source_id() << " -> " << request->destination_id() << std::endl;

   
    PathResult result = findCheapestPath(this->railway_graph, request->source_id(), request->destination_id());

    if(!result.found){
        return grpc::Status(grpc::StatusCode::NOT_FOUND,"No route available between these stations");
    }

    response->set_total_price(static_cast<int32_t>(result.total_price));
    
    for(const std::string& station_id:result.station_ids){
            response->add_path_stations_ids(station_id);
    }
    
    return grpc::Status::OK;
}
