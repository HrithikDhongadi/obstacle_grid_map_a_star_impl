#include <iostream>
#include <queue>
#include <vector>

// Compile Statement
// g++ -std=c++17 -o demo_node demo_node.cpp

struct Node {
    int x, y;
    double g, h;

    double f() const { return g + h; }
};

// --- Option 1: Using operator< inside Node ---
struct NodeWithOp {
    int x, y;
    double g, h;

    double f() const { return g + h; }

    bool operator<(const NodeWithOp& other) const {
        return f() > other.f(); // reversed for min-heap
    }
};

int main() {
    // -------- Option 1: implicit comparator via operator< --------
    std::priority_queue<NodeWithOp> pq1;

    pq1.push({0,0,0,5}); // f=5
    pq1.push({1,0,2,2}); // f=4
    pq1.push({2,2,3,1}); // f=4

    std::cout << "Using operator< in Node:\n";
    while (!pq1.empty()) {
        auto n = pq1.top(); pq1.pop();
        std::cout << "  Node(" << n.x << "," << n.y << ") f=" << n.f() << "\n";
    }

    // -------- Option 2: explicit comparator (lambda) --------
    auto cmp = [](const Node& a, const Node& b) {
        return a.f() > b.f(); // same trick: min-heap
    };
    std::priority_queue<Node, std::vector<Node>, decltype(cmp)> pq2(cmp);

    pq2.push({0,0,0,5}); // f=5
    pq2.push({1,0,2,2}); // f=4
    pq2.push({2,2,3,1}); // f=4

    std::cout << "\nUsing custom comparator lambda:\n";
    while (!pq2.empty()) {
        auto n = pq2.top(); pq2.pop();
        std::cout << "  Node(" << n.x << "," << n.y << ") f=" << n.f() << "\n";
    }

    return 0;
}
