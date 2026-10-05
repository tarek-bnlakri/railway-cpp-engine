#include <gtest/gtest.h>
#include "../src/graph.h"

// A Unit Test is just a function that runs some code and checks if the result matches what you expect.
// The syntax is TEST(TestSuiteName, TestName)

TEST(GraphTest, CanAddAndRetrieveEdges) {
    // 1. Setup
    Graph g;
    
    // 2. Action (Add an edge from London to Paris)
    g.addEdge("London", "Paris", 150.0, "ROUTE_001");
    g.addEdge("Paris", "Germany", 180.0, "ROUTE_002");
    g.addEdge("London", "Germany", 1800.0, "ROUTE_002");
    
    // 3. Assertions (Check if it worked!)
    auto neighbors = g.getNeighbors("London");
    
    // We expect London tfile:///home/tarek/C++_prepare_for_test
    EXPECT_EQ(neighbors.size(), 2);
    
    // We expect that neighbor's destination to be "Paris"
    EXPECT_EQ(neighbors[0].destination_id, "Paris");
    
    // We expect the weight to be 150.0
    EXPECT_EQ(neighbors[0].weight, 150.0);
}

// TASK: Write a second test called 'HandlesEmptyNode'
// 1. Create a Graph.
// 2. Do NOT add any edges to it.
// 3. Ask for the neighbors of "Berlin".
// 4. Use EXPECT_EQ to check that the size of the returned vector is exactly 0.
TEST(GraphTest, HandlesEmptyNode) {
    Graph g;
    auto neighbors = g.getNeighbors("London");
    EXPECT_EQ(neighbors.size(), 0);
    


}

