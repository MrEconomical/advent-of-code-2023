#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::vector;

const long long EXPAND = 1'000'000 - 1;

struct Galaxy {
    long long row;
    long long col;
};

istream* get_input_stream() {
    return new ifstream("expansion.txt");
}

bool check_row_empty(const vector<string>& image, size_t row) {
    bool empty{true};
    for (size_t c = 0; c < image[row].size(); c ++) {
        if (image[row][c] != '.') {
            empty = false;
            break;
        }
    }
    return empty;
}

bool check_col_empty(const vector<string>& image, size_t col) {
    bool empty{true};
    for (size_t r = 0; r < image.size(); r ++) {
        if (image[r][col] != '.') {
            empty = false;
            break;
        }
    }
    return empty;
}

int main() {
    istream& input = *get_input_stream();

    vector<string> image;
    string line;
    while (std::getline(input, line)) {
        image.push_back(line);
    }
    size_t num_rows = image.size();
    size_t num_cols = image[0].size();

    vector<bool> empty_rows(num_rows, false);
    vector<bool> empty_cols(num_cols, false);
    for (size_t r = 0; r < num_rows; r ++) {
        if (check_row_empty(image, r)) {
            empty_rows[r] = true;
        }
    }
    for (size_t c = 0; c < num_cols; c ++) {
        if (check_col_empty(image, c)) {
            empty_cols[c] = true;
        }
    }

    vector<Galaxy> galaxies;
    long long row_expand{0};
    long long col_expand{0};
    for (int r = 0; r < num_rows; r ++) {
        if (empty_rows[r]) {
            row_expand += EXPAND;
            continue;
        }
        for (int c = 0; c < num_cols; c ++) {
            if (empty_cols[c]) {
                col_expand += EXPAND;
            } else if (image[r][c] == '#') {
                galaxies.push_back(Galaxy{r + row_expand, c + col_expand});
            }
        }
        col_expand = 0;
    }

    long long total{0};
    for (size_t a = 0; a < galaxies.size(); a ++) {
        for (size_t b = a + 1; b < galaxies.size(); b ++) {
            long long distance = std::abs(galaxies[a].row - galaxies[b].row)
                + std::abs(galaxies[a].col - galaxies[b].col);
            total += distance;
        }
    }

    std::cout << "Total distance: " << total << "\n";
}