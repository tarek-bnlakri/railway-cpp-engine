#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct Edge{
    std::string destination_id;
    std::string route_id;
    float weight;
};


class Graph{
  private:
    std::unordered_map<std::string, std::vector<Edge>> adjacency_list;
  public:
    void addEdge(const std::string& source,const std::string& destination, float weight, const std::string& route_id);
    std::vector<Edge> getNeighbors(const std::string& node) const;
    
}; 