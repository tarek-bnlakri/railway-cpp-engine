#pragma once
#include <grpcpp/grpcpp.h>
#include "route_search.grpc.pb.h"
#include "graph.h"

class RouteSearchServiceImpl final : public RouteSearchService::Service {
private:
    Graph railway_graph;

public:
    RouteSearchServiceImpl(); 

    grpc::Status FindCheapestPath(
        grpc::ServerContext* context, 
        const PathRequest* request, 
        PathResponse* response) override;
};
