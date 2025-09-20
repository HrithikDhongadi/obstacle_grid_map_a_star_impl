#include "map.hpp"
#include "a_star.hpp"
#include <iostream>

// complie statement
// g++ -std=c++17 -o pathfinding main.cpp map.cpp a_star.cpp `pkg-config --cflags --libs opencv4`

int main() {
    GridMap map(100, 100);

    // Generate random map
    map.generateRandomMap(0.25);

    // Print ASCII
    map.print();

    // Run A*
    auto path = AStar::findPath(map);

    if (path.empty()) {
        std::cout << "No path found!\n";
    } else {
        std::cout << "Path found with " << path.size() << " steps.\n";
    }

    // Visualize with path
    map.visualizeWithPath(path, 10);

    return 0;
}
