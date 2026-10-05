#pragma once
#include <string>
#include <vector>
#include "graph.h"

// A struct to hold the final result of our search
struct PathResult {
    float total_price;
    std::vector<std::string> station_ids;
    std::vector<std::string> route_ids;
    bool found;
};

// The standalone Dijkstra function (just like your TypeScript one!)
PathResult findCheapestPath(const Graph& graph, const std::string& source_id, const std::string& destination_id);
