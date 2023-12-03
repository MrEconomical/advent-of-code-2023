#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <utility>
#include <vector>

using std::ifstream, std::istream;
using std::pair, std::string, std::vector;

const string digit_words[10] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

istream* get_input_stream() {
    return new ifstream("trebuchet.txt");
}

int get_digit(const string& line, size_t pos) {
    if (line[pos] >= '0' && line[pos] <= '9') {
        return line[pos] - '0';
    }
    for (int digit = 0; digit <= 9; digit ++) {
        if (line.compare(pos, digit_words[digit].size(), digit_words[digit]) == 0) {
            return digit;
        }
    }
    return -1;
}

int main() {
    istream& input = *get_input_stream();
    
    int total{0};
    pair<int, int> value{-1, -1};
    string line;

    while (std::getline(input, line)) {
        for (size_t p = 0; p < line.size(); p ++) {
            int digit = get_digit(line, p);
            if (digit != -1) {
                if (value.first == -1) {
                    value.first = digit;
                }
                value.second = digit;
            }
        }

        total += value.first * 10 + value.second;
        value.first = -1;
        value.second = -1;
    }

    std::cout << "Total value: " << total << "\n";
}