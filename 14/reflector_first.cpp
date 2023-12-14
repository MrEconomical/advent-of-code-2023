#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::vector;

istream* get_input_stream() {
    return new ifstream("reflector.txt");
}

void shift_column(vector<string>& map, size_t col) {
    size_t free_row{0};
    for (size_t r = 0; r < map.size(); r ++) {
        if (map[r][col] == 'O') {
            if (free_row < r) {
                map[free_row][col] = 'O';
                map[r][col] = '.';
            }
            if (free_row <= r) {
                free_row ++;
            }
        } else if (map[r][col] == '#') {
            free_row = r + 1;
        }
        while (free_row < map.size() && map[free_row][col] != '.') {
            free_row ++;
        }
    }
}

int calc_column_load(const vector<string>& map, size_t col) {
    int load{0};
    for (size_t r = 0; r < map.size(); r ++) {
        if (map[r][col] == 'O') {
            load += map.size() - r;
        }
    }
    return load;
}

int main() {
    istream& input = *get_input_stream();

    vector<string> map;
    string line;
    while (std::getline(input, line)) {
        map.push_back(line);
    }

    int load{0};
    for (size_t c = 0; c < map[0].size(); c ++) {
        shift_column(map, c);
        load += calc_column_load(map, c);
    }

    std::cout << "Total load: " << load << "\n";
}