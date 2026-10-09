#pragma once
#include <string>
#include <vector>
#include "graph.h"

struct PathResult {
    float total_price;
    std::vector<std::string> station_ids;
    std::vector<std::string> route_ids;
    bool found;
};

PathResult findCheapestPath(const Graph& graph, const std::string& source_id, const std::string& destination_id);
