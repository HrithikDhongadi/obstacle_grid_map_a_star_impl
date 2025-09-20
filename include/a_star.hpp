#ifndef A_STAR_HPP
#define A_STAR_HPP

#include "map.hpp"
#include <vector>
#include <utility>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <limits>

class AStar {
public:
    static std::vector<std::pair<int,int>> findPath(const GridMap& map);
};

#endif // A_STAR_HPP
