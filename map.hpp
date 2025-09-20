#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <opencv2/opencv.hpp>
#include <random>
#include <ctime>

enum class CellType {
    FREE,
    OBSTACLE,
    START,
    GOAL
};

class GridMap {
public:
    GridMap(int width, int height);

    // Accessors
    int getWidth() const;
    int getHeight() const;

    CellType getCell(int x, int y) const;
    void setCell(int x, int y, CellType type);

    void setStart(int x, int y);
    void setGoal(int x, int y);

    std::pair<int, int> getStart() const;
    std::pair<int, int> getGoal() const;

    void generateRandomMap(double obstacleProb = 0.2);

    void print() const;              // ASCII visualizer
    void visualize(int cellSize = 40) const; // OpenCV visualizer
    void visualizeWithPath(const std::vector<std::pair<int,int>>& path, int cellSize = 40) const;


private:
    int width_;
    int height_;
    std::vector<CellType> grid_;
    std::pair<int, int> start_;
    std::pair<int, int> goal_;

    bool inBounds(int x, int y) const;
};

#endif // MAP_HPP
