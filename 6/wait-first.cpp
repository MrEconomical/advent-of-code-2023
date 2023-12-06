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

vector<int> parse_nums(const string& str) {
    string content = str.substr(str.find(':') + 1);
    stringstream nums_stream(content);

    vector<int> nums;
    string num;
    while (std::getline(nums_stream, num, ' ')) {
        if (num != "") {
            nums.push_back(std::stoi(num));
        }
    }

    return nums;
}

int main() {
    istream& input = *get_input_stream();

    string times_str;
    string distances_str;
    std::getline(input, times_str);
    std::getline(input, distances_str);

    vector<int> times = parse_nums(times_str);
    vector<int> distances = parse_nums(distances_str);

    int num_ways{1};
    for (size_t r = 0; r < times.size(); r ++) {
        int possible{0};
        for (int s = 1; s < times[r]; s ++) {
            if (s * (times[r] - s) > distances[r]) {
                possible ++;
            }
        }
        num_ways *= possible;
    }

    std::cout << "Number of ways: " << num_ways << "\n";
}