#include <gtest/gtest.h>
#include "../src/dijkstra.h"

TEST(DijkstraTest, FindsCheapestPath) {
    Graph g;
    // Route 1: A -> B -> C (Cost 100 + 100 = 200)
    g.addEdge("A", "B", 100.0, "ROUTE_AB");
    g.addEdge("B", "C", 100.0, "ROUTE_BC");
    
    // Route 2: A -> C directly (Cost 300)
    g.addEdge("A", "C", 300.0, "ROUTE_AC");

    PathResult result = findCheapestPath(g, "A", "C");

    
    EXPECT_TRUE(result.found);
    
    EXPECT_EQ(result.total_price, 200.0);
    
    ASSERT_EQ(result.station_ids.size(), 3);
    EXPECT_EQ(result.station_ids[0], "A");
    EXPECT_EQ(result.station_ids[1], "B");
    EXPECT_EQ(result.station_ids[2], "C");
    
    ASSERT_EQ(result.route_ids.size(), 2);
    EXPECT_EQ(result.route_ids[0], "ROUTE_AB");
    EXPECT_EQ(result.route_ids[1], "ROUTE_BC");
}

TEST(DijkstraTest, HandlesUnreachableDestination) {
    Graph g;
    g.addEdge("A", "B", 100.0, "ROUTE_AB");
    g.addEdge("C", "D", 50.0, "ROUTE_CD");

    PathResult result = findCheapestPath(g, "A", "D");

    EXPECT_FALSE(result.found);
    EXPECT_EQ(result.total_price, 0.0);
    EXPECT_EQ(result.station_ids.size(), 0);
}
