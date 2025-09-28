#include "a_star.hpp"

// Node structure for the priority queue
struct Node {
    int x, y; // coordinates
    double g; // cost so far
    double h; // heuristic

    double f() const { return g + h; } ; // total cost

    bool operator<(const Node& other) const {
        return f() > other.f(); // min-heap based on f
    }
};

static int encode(int x, int y, int width) {
    return y * width + x;
}

std::vector<std::pair<int,int>> AStar::findPath(const GridMap& map) {
    int w = map.getWidth();
    int h = map.getHeight();
    auto [sx, sy] = map.getStart();
    auto [gx, gy] = map.getGoal();

    // Manhattan heuristic
    auto heuristic = [&](int x, int y) {
        return std::abs(x - gx) + std::abs(y - gy);
    };

    // // Euclidean heuristic
    // auto heuristic = [&](int x, int y) {
    //     return std::sqrt((x - gx) * (x - gx) + (y - gy) * (y - gy));
    // };

    std::priority_queue<Node> open;
    std::vector<std::vector<bool>> closed(h, std::vector<bool>(w, false));
    std::vector<std::vector<double>> gScore(h, std::vector<double>(w, std::numeric_limits<double>::infinity()));
    std::unordered_map<int, std::pair<int,int>> parent;

    gScore[sy][sx] = 0.0;
    open.push({sx, sy, 0.0, static_cast<double>(heuristic(sx, sy))});

    std::vector<std::pair<int,int>> dirs = {
        {1,0},{-1,0},{0,1},{0,-1}
    };

    while (!open.empty()) {
        Node cur = open.top(); // Take the node with the lowest f value
        open.pop(); // Remove it from the Open List as its going to be fully explored/evaluated

        if (closed[cur.y][cur.x]) continue;
        closed[cur.y][cur.x] = true; // Mark it as evaluated by adding it to the Closed List

        // If we reached the goal, reconstruct the path
        if (cur.x == gx && cur.y == gy) {
            // reconstruct path
            std::vector<std::pair<int,int>> path;
            int cx = gx, cy = gy; // current x,y
            while (!(cx == sx && cy == sy)) { // until we reach start
                path.push_back({cx, cy}); // add to path
                auto p = parent[encode(cx, cy, w)]; // get parent
                cx = p.first; // move to parent x
                cy = p.second; // move to parent y
            }
            path.push_back({sx, sy}); // add start

            // // Print Unreversed (Goal to Start) Path Coordinates
            // std::cout << "Unreversed (Goal to Start) Path Coordinates:\n";
            // for (auto& it : path)
            //     std::cout << "(" << it.first << ", " << it.second << ")\n";   // print each coordinate

            std::reverse(path.begin(), path.end()); // start to goal

            // // Print Reversed (Start to Goal) Path Coordinates
            // std::cout << "Reversed (Start to Goal) Path Coordinates:\n";
            // for (const auto& p : path)
            //     std::cout << "(" << p.first << ", " << p.second << ")\n"; // print each coordinate

            return path;
        }

        for (auto [dx,dy] : dirs) {
            int nx = cur.x + dx;
            int ny = cur.y + dy;
            if (nx < 0 || ny < 0 || nx >= w || ny >= h) continue;  // Out of bounds condition
            if (map.getCell(nx, ny) == CellType::OBSTACLE) continue; // Obstacle condition
            if (closed[ny][nx]) continue; // Already evaluated

            double tentative_g = cur.g + 1.0; // cost of moving one step

            if (tentative_g < gScore[ny][nx]) {
                gScore[ny][nx] = tentative_g;
                parent[encode(nx,ny,w)] = {cur.x, cur.y};
                open.push({nx, ny, tentative_g, static_cast<double>(heuristic(nx, ny))});
            }
        }
    }

    return {}; // no path found
}
