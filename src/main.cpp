#include "map.hpp"
#include "a_star.hpp"
#include <iostream>
#include <chrono>

// complie statement
// g++ -std=c++14 -I/usr/local/include/opencv4 -Iinclude -o main src/main.cpp src/map.cpp src/a_star.cpp -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc

int main() {
    GridMap map(100, 100);

    // Generate random map
    map.generateRandomMap(0.25);

    // Print ASCII
    map.print();

    // Run A*
    auto start = std::chrono::high_resolution_clock::now();
    auto path = AStar::findPath(map);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "A* took " << elapsed.count() << " seconds.\n";
    
    if (path.empty()) {
        std::cout << "No path found First goal!\n";
    } else {
        std::cout << "First Path found with " << path.size() << " steps.\n";
    }

    // Set new start and goal randomly
    std::uniform_int_distribution<int> dist(0, 99);
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));

    map.setStart(dist(rng), dist(rng));
    map.setGoal(dist(rng), dist(rng));
    
    start = std::chrono::high_resolution_clock::now();
    auto path2 = AStar::findPath(map);

    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "A* took " << elapsed.count() << " seconds.\n";

    if (path.empty()) {
        std::cout << "No path found Second Goal!\n";
    } else {
        std::cout << "Second Path found with " << path2.size() << " steps.\n";
    }
    
    // Visualize with path
    // The pair is a coodinate defined as std::pair<int,int> where first is x and second is y
    // The inner vector is a collection of coordinates that form a path
    // The outer vector is a collection of such paths
    auto paths = std::vector<std::vector<std::pair<int,int>>>{path, path2};
    map.visualizeWithPath(paths, 10);

    return 0;
}
