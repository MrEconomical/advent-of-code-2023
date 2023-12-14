#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::vector;

istream* get_input_stream() {
    return new ifstream("incidence.txt");
}

int check_row_reflect(const vector<string>& image) {
    int num_rows = image.size();
    for (int r = 1; r < image.size(); r ++) {
        bool valid{true};
        int max_distance = std::min(r, num_rows - r);
        for (int d = 0; d < max_distance; d ++) {
            if (image[r - d - 1] != image[r + d]) {
                valid = false;
                break;
            }
        }
        if (valid) {
            return r;
        }
    }
    return -1;
}

bool check_reflect(const string& str, int pos) {
    bool valid{true};
    int max_distance = std::min(pos, static_cast<int>(str.size()) - pos);
    for (int d = 0; d < max_distance; d ++) {
        if (str[pos - d - 1] != str[pos + d]) {
            valid = false;
            break;
        }
    }
    return valid;
}

int check_col_reflect(const vector<string>& image) {
    for (int c = 1; c < image[0].size(); c ++) {
        bool valid{true};
        for (const string& row : image) {
            if (!check_reflect(row, c)) {
                valid = false;
                break;
            }
        }
        if (valid) {
            return c;
        }
    }
    return -1;
}

int find_mirror(const vector<string>& image) {
    int row_reflect = check_row_reflect(image);
    if (row_reflect != -1) {
        return row_reflect * 100;
    }
    return check_col_reflect(image);
}

int main() {
    istream& input = *get_input_stream();

    int total{0};
    vector<string> image;
    string line;
    while (std::getline(input, line)) {
        if (line == "") {
            total += find_mirror(image);
            image.clear();
        } else {
            image.push_back(line);
        }
    }
    total += find_mirror(image);

    std::cout << "Total: " << total << "\n";
}