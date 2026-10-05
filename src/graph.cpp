#include "graph.h"

void Graph::addEdge(const std::string& source,const std::string& destination, float weight, const std::string& route_id){
    adjacency_list[source].push_back(Edge{destination,route_id,weight});

}
std:: vector<Edge> Graph::getNeighbors(const std::string& node) const{
    auto it  =adjacency_list.find(node);
    
    if (it != adjacency_list.end()){
        return it->second;
    }
    else{
        return {};
    }
}