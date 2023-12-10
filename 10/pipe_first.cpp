#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::vector;

size_t num_rows;
size_t num_cols;

istream* get_input_stream() {
    return new ifstream("pipe.txt");
}

bool check_up_pipe(const vector<string>& lines, size_t row, size_t col) {
    return lines[row][col] == '|'
        || lines[row][col] == '7'
        || lines[row][col] == 'F'
        || lines[row][col] == 'S';
}

bool check_down_pipe(const vector<string>& lines, size_t row, size_t col) {
    return lines[row][col] == '|'
        || lines[row][col] == 'L'
        || lines[row][col] == 'J'
        || lines[row][col] == 'S';
}

bool check_left_pipe(const vector<string>& lines, size_t row, size_t col) {
    return lines[row][col] == '-'
        || lines[row][col] == 'L'
        || lines[row][col] == 'F'
        || lines[row][col] == 'S';
}

bool check_right_pipe(const vector<string>& lines, size_t row, size_t col) {
    return lines[row][col] == '-'
        || lines[row][col] == 'J'
        || lines[row][col] == '7'
        || lines[row][col] == 'S';
}

int search_loop(
    const vector<string>& lines,
    vector<vector<bool>>& visited,
    size_t row,
    size_t col
);

int search_adjacent(
    const vector<string>& lines,
    vector<vector<bool>>& visited,
    size_t row,
    size_t col
) {
    int max_result{-1};
    if (row > 0 && check_up_pipe(lines, row - 1, col)) {
        int up_result = search_loop(lines, visited, row - 1, col);
        if (up_result > max_result) {
            max_result = up_result;
        }
    }
    if (row < num_rows - 1 && check_down_pipe(lines, row + 1, col)) {
        int down_result = search_loop(lines, visited, row + 1, col);
        if (down_result > max_result) {
            max_result = down_result;
        }
    }

    if (col > 0 && check_left_pipe(lines, row, col - 1)) {
        int left_result = search_loop(lines, visited, row, col - 1);
        if (left_result > max_result) {
            max_result = left_result;
        }
    }
    if (col < num_cols - 1 && check_right_pipe(lines, row, col + 1)) {
        int right_result = search_loop(lines, visited, row, col + 1);
        if (right_result > max_result) {
            max_result = right_result;
        }
    }

    return max_result + 1;
}

int search_loop(
    const vector<string>& lines,
    vector<vector<bool>>& visited,
    size_t row,
    size_t col
) {
    if (lines[row][col] == 'S') {
        return 0;
    } else if (visited[row][col]) {
        return -1;
    }
    visited[row][col] = true;
    return search_adjacent(lines, visited, row, col);
}

int find_loop(const vector<string>& lines, size_t row, size_t col) {
    vector<vector<bool>> visited(num_rows, vector<bool>(num_cols, false));
    visited[row][col] = true;
    return search_adjacent(lines, visited, row, col);
}

int main() {
    istream& input = *get_input_stream();

    vector<string> lines;
    string line;
    while (std::getline(input, line)) {
        lines.push_back(line);
    }
    num_rows = lines.size();
    num_cols = lines[0].size();

    int loop_size;
    for (size_t r = 0; r < num_rows; r ++) {
        for (size_t c = 0; c < num_cols; c ++) {
            if (lines[r][c] == 'S') {
                loop_size = find_loop(lines, r, c);
                break;
            }
        }
    }

    std::cout << "Farthest pipe: " << loop_size / 2 << "\n";
}