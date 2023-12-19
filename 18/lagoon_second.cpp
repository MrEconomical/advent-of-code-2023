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
    long long x;
    long long y;
};

istream* get_input_stream() {
    return new ifstream("lagoon.txt");
}

int main() {
    istream& input = *get_input_stream();

    vector<Point> points;
    Point current{0, 0};
    points.push_back(current);
    long long perimeter{0};

    string move;
    while (input >> move >> move >> move) {
        long long distance = std::stoll(move.substr(2, 5), nullptr, 16);
        switch (move[7]) {
            case '0':
                current.x += distance;
                break;
            case '1':
                current.y -= distance;
                break;
            case '2':
                current.x -= distance;
                break;
            case '3':
                current.y += distance;
                break;
        }
        points.push_back(current);
        perimeter += distance;
    }

    long long area{0};
    for (size_t p = 0; p < points.size() - 1; p ++) {
        area += points[p].x * points[p + 1].y;
        area -= points[p].y * points[p + 1].x;
    }
    area = std::abs(area) / 2;
    area += perimeter / 2 + 1;

    std::cout << "Total area: " << area << "\n";
}