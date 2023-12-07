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

bool check_is_symbol(const vector<string>& schematic, size_t row, size_t col) {
    return row > 0 && row < schematic.size()
        && col > 0 && col < schematic[row].size()
        && schematic[row][col] != '.'
        && !check_is_digit(schematic[row][col]);
}

bool check_around_symbol(const vector<string>& schematic, size_t row, size_t col) {
    return check_is_symbol(schematic, row - 1, col - 1)
        || check_is_symbol(schematic, row - 1, col)
        || check_is_symbol(schematic, row - 1, col + 1)
        || check_is_symbol(schematic, row, col - 1)
        || check_is_symbol(schematic, row, col + 1)
        || check_is_symbol(schematic, row + 1, col - 1)
        || check_is_symbol(schematic, row + 1, col)
        || check_is_symbol(schematic, row + 1, col + 1);
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
    for (Number num : numbers) {
        for (size_t c = num.col; c < num.col + num.len; c ++) {
            if (check_around_symbol(schematic, num.row, c)) {
                total += std::stoi(schematic[num.row].substr(num.col, num.len));
                break;
            }
        }
    }

    std::cout << "Total value: " << total << "\n";
}