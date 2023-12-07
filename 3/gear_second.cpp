#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::vector;

struct Number {
    size_t row;
    size_t col;
    size_t len;
};

istream* get_input_stream() {
    return new ifstream("gear.txt");
}

bool check_is_digit(char c) {
    return c >= '0' && c <= '9';
}

vector<Number> get_numbers(const vector<string>& schematic) {
    vector<Number> numbers;
    Number current{string::npos, string::npos, 0};

    for (size_t r = 0; r < schematic.size(); r ++) {
        for (size_t c = 0; c < schematic[r].size(); c ++) {
            if (!check_is_digit(schematic[r][c])) {
                if (current.row != string::npos) {
                    numbers.push_back(current);
                    current = Number{string::npos, string::npos, 0};
                }
            } else {
                if (current.row == string::npos) {
                    current = Number{r, c, 1};
                } else {
                    current.len ++;
                }
            }
        }

        if (current.row != string::npos) {
            numbers.push_back(current);
            current = Number{string::npos, string::npos, 0};
        }
    }

    return numbers;
}

vector<Number> get_adjacent_nums(const vector<Number>& numbers, size_t row, size_t col) {
    vector<Number> adjacent;
    for (Number num : numbers) {
        if ((num.row > 0 && row < num.row - 1) || row > num.row + 1) {
            continue;
        }
        if ((num.col > 0 && col < num.col - 1) || col > num.col + num.len) {
            continue;
        }
        adjacent.push_back(num);
    }
    return adjacent;
}

int parse_num(const vector<string>& schematic, Number num) {
    return std::stoi(schematic[num.row].substr(num.col, num.len));
}

int main() {
    istream& input = *get_input_stream();

    vector<string> schematic;
    string line;
    while (std::getline(input, line)) {
        schematic.push_back(line);
    }

    vector<Number> numbers = get_numbers(schematic);
    int total{0};
    for (size_t r = 0; r < schematic.size(); r ++) {
        for (size_t c = 0; c < schematic[r].size(); c ++) {
            if (schematic[r][c] != '*') {
                continue;
            }
            vector<Number> adjacent = get_adjacent_nums(numbers, r, c);
            if (adjacent.size() == 2) {
                total += parse_num(schematic, adjacent[0]) * parse_num(schematic, adjacent[1]);
            }
        }
    }

    std::cout << "Total value: " << total << "\n";
}