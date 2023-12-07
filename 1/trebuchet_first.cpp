#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <utility>
#include <vector>

using std::ifstream, std::istream;
using std::pair, std::string, std::vector;

istream* get_input_stream() {
    return new ifstream("trebuchet.txt");
}

int main() {
    istream& input = *get_input_stream();
    
    int total{0};
    pair<int, int> value{-1, -1};
    string line;
    
    while (std::getline(input, line)) {
        for (char c : line) {
            if (c >= '0' && c <= '9') {
                if (value.first == -1) {
                    value.first = c - '0';
                }
                value.second = c - '0';
            }
        }

        total += value.first * 10 + value.second;
        value.first = -1;
        value.second = -1;
    }

    std::cout << "Total value: " << total << "\n";
}