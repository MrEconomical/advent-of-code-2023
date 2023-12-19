#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <limits>
#include <string>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::vector;

const size_t MAX_STREAM_LEN = std::numeric_limits<std::streamsize>::max();

struct Point {
    int x;
    int y;
};

istream* get_input_stream() {
    return new ifstream("lagoon.txt");
}

int main() {
    istream& input = *get_input_stream();

    vector<Point> points;
    Point current{0, 0};
    points.push_back(current);
    int perimeter{0};

    char dir;
    string amount;
    while (input >> dir >> amount) {
        input.ignore(MAX_STREAM_LEN, '\n');
        int distance = std::stoi(amount);
        if (dir == 'U') {
            current.y += distance;
        } else if (dir == 'D') {
            current.y -= distance;
        } else if (dir == 'L') {
            current.x -= distance;
        } else if (dir == 'R') {
            current.x += distance;
        }
        points.push_back(current);
        perimeter += distance;
    }

    int area{0};
    for (size_t p = 0; p < points.size() - 1; p ++) {
        area += points[p].x * points[p + 1].y;
        area -= points[p].y * points[p + 1].x;
    }
    area = std::abs(area) / 2;
    area += perimeter / 2 + 1;

    std::cout << "Total area: " << area << "\n";
}