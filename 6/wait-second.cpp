#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::stringstream, std::vector;

istream* get_input_stream() {
    return new ifstream("wait.txt");
}

long long parse_num(const string& str) {
    string content = str.substr(str.find(':') + 1);
    stringstream nums_stream(content);

    string total_num;
    string num;
    while (std::getline(nums_stream, num, ' ')) {
        if (num != "") {
            total_num += num;
        }
    }

    return std::stoll(total_num);
}

int main() {
    istream& input = *get_input_stream();

    string times_str;
    string distances_str;
    std::getline(input, times_str);
    std::getline(input, distances_str);

    long long time = parse_num(times_str);
    long long distance = parse_num(distances_str);
    long long num_ways{0};
    for (long long s = 1; s < time; s ++) {
        if (s * (time - s) > distance) {
            num_ways ++;
        }
    }

    std::cout << "Number of ways: " << num_ways << "\n";
}