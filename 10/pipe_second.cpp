#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <tuple>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::vector;

enum class Dir {
    Up,
    Down,
    Left,
    Right,
};

struct Pos {
    size_t row;
    size_t col;
    Dir dir;
};

size_t num_rows;
size_t num_cols;

istream* get_input_stream() {
    return new ifstream("pipe.txt");
}

Dir change_dir(char pipe, Dir prev) {
    if (prev == Dir::Up) {
        if (pipe == '7') {
            return Dir::Left;
        } else if (pipe == 'F') {
            return Dir::Right;
        }
    } else if (prev == Dir::Down) {
        if (pipe == 'L') {
            return Dir::Right;
        } else if (pipe == 'J') {
            return Dir::Left;
        }
    } else if (prev == Dir::Left) {
        if (pipe == 'L') {
            return Dir::Up;
        } else if (pipe == 'F') {
            return Dir::Down;
        }
    } else if (prev == Dir::Right) {
        if (pipe == 'J') {
            return Dir::Up;
        } else if (pipe == '7') {
            return Dir::Down;
        }
    }
    return prev;
}

Pos update_pos(const vector<string>& map, Pos pos, Dir next) {
    Pos next_pos;
    if (next == Dir::Up) {
        next_pos = Pos{pos.row - 1, pos.col, next};
    } else if (next == Dir::Down) {
        next_pos = Pos{pos.row + 1, pos.col, next};
    } else if (next == Dir::Left) {
        next_pos = Pos{pos.row, pos.col - 1, next};
    } else if (next == Dir::Right) {
        next_pos = Pos{pos.row, pos.col + 1, next};
    }

    if (next_pos.row < num_rows && next_pos.col < num_cols) {
        next_pos.dir = change_dir(map[next_pos.row][next_pos.col], next);
    }
    return next_pos;
}

bool check_connect(
    const vector<string>& map,
    Pos pos,
    Dir next
) {
    Pos next_pos = update_pos(map, pos, next);
    if (next_pos.row > num_rows - 1 || next_pos.col > num_cols - 1) {
        return false;
    }
    char pipe = map[next_pos.row][next_pos.col];

    if (next == Dir::Up) {
        return pipe == '|' || pipe == '7' || pipe == 'F';
    } else if (next == Dir::Down) {
        return pipe == '|' || pipe == 'L' || pipe == 'J';
    } else if (next == Dir::Left) {
        return pipe == '-' || pipe == 'L' || pipe == 'F';
    }
    return pipe == '-' || pipe == 'J' || pipe == '7';
}

std::tuple<Pos, Pos> get_start_end(const vector<string>& map) {
    for (size_t r = 0; r < num_rows; r ++) {
        for (size_t c = 0; c < num_cols; c ++) {
            if (map[r][c] != 'S') {
                continue;
            }

            Pos current = Pos{r, c, Dir::Up};
            vector<Pos> valid;
            if (check_connect(map, current, Dir::Right)) {
                valid.push_back(update_pos(map, current, Dir::Right));
            }
            if (check_connect(map, current, Dir::Left)) {
                valid.push_back(update_pos(map, current, Dir::Left));
            }
            if (check_connect(map, current, Dir::Up)) {
                valid.push_back(update_pos(map, current, Dir::Up));
            }
            if (check_connect(map, current, Dir::Down)) {
                valid.push_back(update_pos(map, current, Dir::Down));
            }

            return {valid[0], valid[1]};
        }
    }

    return {Pos{0, 0, Dir::Up}, Pos{0, 0, Dir::Up}};
}

Dir get_left_dir(Dir dir) {
    if (dir == Dir::Up) {
        return Dir::Left;
    } else if (dir == Dir::Down) {
        return Dir::Right;
    } else if (dir == Dir::Left) {
        return Dir::Down;
    }
    return Dir::Up;
}

Dir get_right_dir(Dir dir) {
    if (dir == Dir::Up) {
        return Dir::Right;
    } else if (dir == Dir::Down) {
        return Dir::Left;
    } else if (dir == Dir::Left) {
        return Dir::Up;
    }
    return Dir::Down;
}

int walk_path(vector<string>& map, vector<vector<bool>>& path, Pos pos, Pos end_pos) {
    path[pos.row][pos.col] = true;
    if (pos.row == end_pos.row && pos.col == end_pos.col) {
        return 1;
    }
    Pos next = update_pos(map, pos, pos.dir);
    return 1 + walk_path(map, path, next, end_pos);
}

int fill_area(vector<string>& map, const vector<vector<bool>>& path, size_t row, size_t col) {
    if (row > num_rows - 1 || col > num_cols - 1
        || map[row][col] == 'x' || path[row][col] || map[row][col] == 'S') {
        return 0;
    }
    map[row][col] = 'x';
    return 1 + fill_area(map, path, row - 1, col)
        + fill_area(map, path, row + 1, col)
        + fill_area(map, path, row, col - 1)
        + fill_area(map, path, row, col + 1);
}

int get_area(vector<string>& map, const vector<vector<bool>>& path, Pos pos, Dir dir) {
    Pos left_pos = update_pos(map, pos, get_right_dir(dir));
    if (left_pos.row > num_rows - 1 || left_pos.col > num_cols - 1) {
        return 0;
    }
    return fill_area(map, path, left_pos.row, left_pos.col);
}

int fill_path_area(vector<string>& map, const vector<vector<bool>>& path, Pos pos, Dir prev_dir, Pos end_pos) {
    int current_area = get_area(map, path, pos, pos.dir) + get_area(map, path, pos, prev_dir);
    if (pos.row == end_pos.row && pos.col == end_pos.col) {
        return current_area;
    }
    Pos next = update_pos(map, pos, pos.dir);
    return current_area + fill_path_area(map, path, next, pos.dir, end_pos);
}

int main() {
    istream& input = *get_input_stream();

    vector<string> map;
    string line;
    while (std::getline(input, line)) {
        map.push_back(line);
    }
    num_rows = map.size();
    num_cols = map[0].size();

    auto [start_pos, end_pos] = get_start_end(map);

    vector<vector<bool>> path(num_rows, vector<bool>(num_cols, false));
    int path_len = walk_path(map, path, start_pos, end_pos);
    int area = fill_path_area(map, path, start_pos, start_pos.dir, end_pos);

    std::cout << "Path length: " << path_len + 1 << "\n";
    std::cout << "Loop area: " << area << "\n";
}