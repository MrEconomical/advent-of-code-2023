#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <tuple>
#include <vector>

using std::ifstream, std::istream;
using std::tuple, std::string, std::vector;

struct Cell {
    char item;
    bool light[4];
};

istream* get_input_stream() {
    return new ifstream("lava.txt");
}

tuple<size_t, size_t> move_dir(size_t row, size_t col, int dir) {
    if (dir == 0) {
        return {row - 1, col};
    } else if (dir == 1) {
        return {row, col + 1};
    } else if (dir == 2) {
        return {row + 1, col};
    }
    return {row, col - 1};
}

void process_light(
    vector<vector<Cell>>& map,
    size_t row,
    size_t col,
    int dir
) {
    if (row > map.size() - 1 || col > map[0].size() - 1
        || map[row][col].light[dir]) {
        return;
    }
    map[row][col].light[dir] = true;

    if (map[row][col].item == '.'
        || (map[row][col].item == '|' && (dir == 0 || dir == 2))
        || (map[row][col].item == '-' && (dir == 1 || dir == 3))) {
        auto [next_row, next_col] = move_dir(row, col, dir);
        process_light(map, next_row, next_col, dir);
    } else if (map[row][col].item == '/') {
        int next_dir;
        if (dir == 0) {
            next_dir = 1;
        } else if (dir == 1) {
            next_dir = 0;
        } else if (dir == 2) {
            next_dir = 3;
        } else if (dir == 3) {
            next_dir = 2;
        }

        auto [next_row, next_col] = move_dir(row, col, next_dir);
        process_light(map, next_row, next_col, next_dir);
    } else if (map[row][col].item == '\\') {
        int next_dir;
        if (dir == 0) {
            next_dir = 3;
        } else if (dir == 1) {
            next_dir = 2;
        } else if (dir == 2) {
            next_dir = 1;
        } else if (dir == 3) {
            next_dir = 0;
        }

        auto [next_row, next_col] = move_dir(row, col, next_dir);
        process_light(map, next_row, next_col, next_dir);
    } else if (map[row][col].item == '|') {
        auto [up_row, up_col] = move_dir(row, col, 0);
        process_light(map, up_row, up_col, 0);
        auto [down_row, down_col] = move_dir(row, col, 2);
        process_light(map, down_row, down_col, 2);
    } else if (map[row][col].item == '-') {
        auto [right_row, right_col] = move_dir(row, col, 1);
        process_light(map, right_row, right_col, 1);
        auto [left_row, left_col] = move_dir(row, col, 3);
        process_light(map, left_row, left_col, 3);
    }
}

int main() {
    istream& input = *get_input_stream();

    vector<vector<Cell>> map;
    string line;
    while (std::getline(input, line)) {
        vector<Cell> row;
        for (char i : line) {
            row.push_back(Cell{i, {false, false, false, false}});
        }
        map.push_back(row);
    }
    process_light(map, 0, 0, 1);

    int total{0};
    for (size_t r = 0; r < map.size(); r ++) {
        for (size_t c = 0; c < map[0].size(); c ++) {
            if (map[r][c].light[0]
                || map[r][c].light[1]
                || map[r][c].light[2]
                || map[r][c].light[3]) {
                total ++;
            }
        }
    }

    std::cout << "Total: " << total << "\n";
}