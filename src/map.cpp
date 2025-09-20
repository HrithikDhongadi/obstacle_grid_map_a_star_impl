#include "map.hpp"

GridMap::GridMap(int width, int height)
    : width_(width), height_(height),
      grid_(width * height, CellType::FREE),
      start_({-1, -1}), goal_({-1, -1}) {}

int GridMap::getWidth() const { return width_; }
int GridMap::getHeight() const { return height_; }

bool GridMap::inBounds(int x, int y) const {
    return (x >= 0 && x < width_ && y >= 0 && y < height_);
}

CellType GridMap::getCell(int x, int y) const {
    if (!inBounds(x, y)) throw std::out_of_range("Coordinates out of bounds");
    return grid_[y * width_ + x];
}

void GridMap::setCell(int x, int y, CellType type) {
    if (!inBounds(x, y)) throw std::out_of_range("Coordinates out of bounds");
    grid_[y * width_ + x] = type;
}

void GridMap::setStart(int x, int y) {
    if (!inBounds(x, y)) throw std::out_of_range("Start out of bounds");
    start_ = {x, y};
    setCell(x, y, CellType::START);
}

void GridMap::setGoal(int x, int y) {
    if (!inBounds(x, y)) throw std::out_of_range("Goal out of bounds");
    goal_ = {x, y};
    setCell(x, y, CellType::GOAL);
}

std::pair<int, int> GridMap::getStart() const { return start_; }
std::pair<int, int> GridMap::getGoal() const { return goal_; }

void GridMap::print() const {
    std::cout << "GridMap (" << width_ << "x" << height_ << ")\n";
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            switch (getCell(x, y)) {
                case CellType::FREE:     std::cout << "."; break;
                case CellType::OBSTACLE: std::cout << "#"; break;
                case CellType::START:    std::cout << "S"; break;
                case CellType::GOAL:     std::cout << "G"; break;
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void GridMap::visualize(int cellSize) const {
    cv::Mat img(height_ * cellSize, width_ * cellSize, CV_8UC3, cv::Scalar(255, 255, 255));

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            cv::Rect rect(x * cellSize, y * cellSize, cellSize, cellSize);
            cv::Scalar color;

            switch (getCell(x, y)) {
                case CellType::FREE:     color = cv::Scalar(240, 240, 240); break; // light gray
                case CellType::OBSTACLE: color = cv::Scalar(0, 0, 0); break;       // black
                case CellType::START:    color = cv::Scalar(0, 255, 0); break;     // green
                case CellType::GOAL:     color = cv::Scalar(0, 0, 255); break;     // red
            }

            cv::rectangle(img, rect, color, cv::FILLED);
            cv::rectangle(img, rect, cv::Scalar(200, 200, 200), 1); // grid lines
        }
    }

    cv::imshow("GridMap", img);
    cv::waitKey(0);
}

void GridMap::generateRandomMap(double obstacleProb) {
    if (obstacleProb < 0.0 || obstacleProb > 1.0)
        throw std::invalid_argument("Obstacle probability must be between 0 and 1");

    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    // Reset grid
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            if (dist(rng) < obstacleProb) {
                setCell(x, y, CellType::OBSTACLE);
            } else {
                setCell(x, y, CellType::FREE);
            }
        }
    }

    // Place start & goal at random FREE locations
    std::uniform_int_distribution<int> xDist(0, width_ - 1);
    std::uniform_int_distribution<int> yDist(0, height_ - 1);

    int sx, sy, gx, gy;
    do {
        sx = xDist(rng);
        sy = yDist(rng);
    } while (getCell(sx, sy) == CellType::OBSTACLE);

    do {
        gx = xDist(rng);
        gy = yDist(rng);
    } while ((gx == sx && gy == sy) || getCell(gx, gy) == CellType::OBSTACLE);

    setStart(sx, sy);
    setGoal(gx, gy);
}

void GridMap::visualizeWithPath(const std::vector<std::vector<std::pair<int,int>>>& paths, int cellSize) const {
    cv::Mat img(height_ * cellSize, width_ * cellSize, CV_8UC3, cv::Scalar(255, 255, 255));
    
    // Draw map
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            cv::Rect rect(x * cellSize, y * cellSize, cellSize, cellSize);
            cv::Scalar color;

            switch (getCell(x, y)) {
                case CellType::FREE:     color = cv::Scalar(240, 240, 240); break;
                case CellType::OBSTACLE: color = cv::Scalar(0, 0, 0); break;
                case CellType::START:    color = cv::Scalar(0, 255, 0); break;
                case CellType::GOAL:     color = cv::Scalar(0, 0, 255); break;
            }

            cv::rectangle(img, rect, color, cv::FILLED);
            cv::rectangle(img, rect, cv::Scalar(200, 200, 200), 1);
        }
    }

    for (const auto& path : paths) {
        

        // Draw path
        for (size_t i = 1; i < path.size(); ++i) {
            cv::Point p1(path[i-1].first * cellSize + cellSize/2, path[i-1].second * cellSize + cellSize/2);
            cv::Point p2(path[i].first * cellSize + cellSize/2, path[i].second * cellSize + cellSize/2);
            cv::line(img, p1, p2, cv::Scalar(255, 0, 0), 2); // blue path
        }
    }
    

    cv::imshow("GridMap with Path", img);
    cv::waitKey(0);
}

