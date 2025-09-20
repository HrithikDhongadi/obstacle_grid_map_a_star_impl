# Obstacle Grid Map A Star Implementation
A Star implementation on a randomly generated grid map for the optimized path planning of the shortest path.

Final goal is to create a dynamic A Star Implementation of a Object moving towards a goal.

## Usage:

1. Clone the repository

2. Compile the code using the provided Makefile or g++ commands in the comments of main.cpp and demo_node.cpp
  - To use the makefile, simply run `make` in the terminal.
  - For main.cpp:
    g++ -std=c++14 -I/usr/local/include/opencv4 -Iinclude -o main src/main.cpp src/map.cpp src/a_star.cpp -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc
  - For demo_node.cpp:
    g++ -std=c++17 -o demo_node demo_node.cpp

3. Run the compiled binaries:
  - For main.cpp with g++ compilation:
    ./main
  - For main.cpp with makefile:
    ./navigate
  - For demo_node.cpp in tests folder:
    ./demo_node