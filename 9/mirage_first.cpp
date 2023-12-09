#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::stringstream, std::vector;

istream* get_input_stream() {
    return new ifstream("mirage.txt");
}

void parse_values(const string& line, vector<int>& values) {
    stringstream line_stream(line);
    string num;
    while (std::getline(line_stream, num, ' ')) {
        values.push_back(std::stoi(num));
    }
}

bool check_all_zero(const vector<int>& values) {
    bool all_zero{true};
    for (int val : values) {
        if (val != 0) {
            all_zero = false;
            break;
        }
    }
    return all_zero;
}

int extrapolate_value(const vector<int>& values) {
    if (check_all_zero(values)) {
        return 0;
    }
    vector<int> diffs(values.size() - 1);
    for (size_t v = 0; v < values.size() - 1; v ++) {
        diffs[v] = values[v + 1] - values[v];
    }
    return values[values.size() - 1] + extrapolate_value(diffs);
}

int main() {
    istream& input = *get_input_stream();

    int total{0};
    string line;
    vector<int> values;
    while (std::getline(input, line)) {
        parse_values(line, values);
        total += extrapolate_value(values);
        values.clear();
    }

    std::cout << "Total values: " << total << "\n";
}