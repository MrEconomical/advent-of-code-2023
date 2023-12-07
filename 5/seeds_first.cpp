#include <fstream>
#include <iostream>
#include <istream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::stringstream, std::vector;

const size_t MAX_LEN = std::numeric_limits<std::streamsize>::max();

struct Range {
    long long source;
    long long dest;
    long long len;
};

istream* get_input_stream() {
    return new ifstream("seeds.txt");
}

vector<long long> parse_seeds(const string& line) {
    stringstream line_stream(line);
    line_stream.ignore(MAX_LEN, ' ');
    vector<long long> nums;
    string num;
    while (std::getline(line_stream, num, ' ')) {
        nums.push_back(std::stoll(num));
    }
    return nums;
}

Range parse_range(const string& line) {
    stringstream line_stream(line);
    Range range;
    line_stream >> range.dest >> range.source >> range.len;
    return range;
}

int main() {
    istream& input = *get_input_stream();

    string line;
    std::getline(input, line);
    vector<long long> items = parse_seeds(line);
    input.ignore(MAX_LEN, '\n');

    vector<Range> mapping;
    while (std::getline(input, line)) {
        mapping.clear();
        while (std::getline(input, line) && line != "") {
            mapping.push_back(parse_range(line));
        }

        for (size_t i = 0; i < items.size(); i ++) {
            for (Range range : mapping) {
                if (items[i] >= range.source && items[i] < range.source + range.len) {
                    long long offset = items[i] - range.source;
                    items[i] = range.dest + offset;
                    break;
                }
            }
        }
    }

    long long min_location = *std::min_element(items.begin(), items.end());
    std::cout << "Minimum location: " << min_location << "\n";
}