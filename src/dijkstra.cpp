#include "dijkstra.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <limits>
#include <algorithm> // For std::reverse

PathResult findCheapestPath(const Graph& graph, const std::string& source_id, const std::string& destination_id) {
    
    // 1. Setup the data structures (Exactly like your TS code!)
    std::unordered_map<std::string, float> distances;
    
    struct PreviousNode {
        std::string node_id;
        std::string route_id;
    };
    std::unordered_map<std::string, PreviousNode> previous;
    std::unordered_set<std::string> visited;

    // In C++, std::priority_queue is a Max-Heap by default. 
    // This scary-looking line is how we make a Min-Heap that stores pairs of {price, station_id}.
    using HeapElement = std::pair<float, std::string>;
    std::priority_queue<HeapElement, std::vector<HeapElement>, std::greater<HeapElement>> min_heap;

    // TASK: Implement the rest of Dijkstra's algorithm here!
    
    // C++ Hints:
    // - Use min_heap.push({0.0, source_id}) to add to the heap.
    // - Use min_heap.top() to get the smallest element, and min_heap.pop() to remove it from the heap.
    // - Infinity in C++ is: std::numeric_limits<float>::infinity()
    
    
    
    // If we never reach the destination:
    return {0.0, {}, {}, false};
}
