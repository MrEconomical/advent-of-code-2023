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
    return new ifstream("lens.txt");
}

int calc_hash(const string& step) {
    int hash{0};
    for (char c : step) {
        hash += c;
        hash = (hash * 17) % 256;
    }
    return hash;
}

int main() {
    istream& input = *get_input_stream();

    string line;
    std::getline(input, line);
    stringstream line_stream(line);

    int total{0};
    string step;
    while (std::getline(line_stream, step, ',')) {
        total += calc_hash(step);
    }

    std::cout << "Total: " << total << "\n";
}