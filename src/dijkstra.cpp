#include "dijkstra.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <limits>
#include <algorithm>

PathResult findCheapestPath(const Graph& graph, const std::string& source_id, const std::string& destination_id) {
    
    std::unordered_map<std::string, float> distances;
    
    struct PreviousNode {
        std::string node_id;
        std::string route_id;
    };
    std::unordered_map<std::string, PreviousNode> previous;
    std::unordered_set<std::string> visited;

  
    using HeapElement = std::pair<float, std::string>;
    std::priority_queue<HeapElement, std::vector<HeapElement>, std::greater<HeapElement>> min_heap;
    
    distances[source_id]=0.0f;
    min_heap.push({0.0f,source_id});
    while(!min_heap.empty()){
        auto current = min_heap.top();
        min_heap.pop();
        
        float current_distances = current.first;
        std::string currunt_id = current.second;

        if (visited.find(currunt_id) != visited.end() ){
            continue;
        }
        visited.insert(currunt_id);

        if( currunt_id == destination_id){
            break;
        }

        for (const auto& edge:graph.getNeighbors(currunt_id)){
            if (visited.find(edge.destination_id) != visited.end() ){
                continue;
            }
            float new_dist = current.first + edge.weight;

            auto dist_it = distances.find(edge.destination_id);
            float old_dist = (dist_it != distances.end())? dist_it->second : std::numeric_limits<float>::infinity();

            if (new_dist <old_dist){
                distances[edge.destination_id]=new_dist;
                previous[edge.destination_id]= {currunt_id, edge.route_id};
                min_heap.push({new_dist,edge.destination_id});
            }
        }
    }
    if (distances.find(destination_id) == distances.end()){
        return {0.0f,{},{},false};
    }
    std::vector<std::string> path_stations;
    std::vector<std::string> path_routes;

    std::string curr = destination_id;

    while(curr != source_id){
        auto prev_node = previous[curr];
        path_stations.push_back(curr);
        path_routes.push_back(prev_node.route_id);
        curr = prev_node.node_id;

    }
    path_stations.push_back(source_id);

    std::reverse(path_stations.begin(),path_stations.end());
    std::reverse(path_routes.begin(),path_routes.end());

    return {distances[destination_id],path_stations,path_routes,true};
    
    
    // If we never reach the destination:
    return {0.0, {}, {}, false};
}
