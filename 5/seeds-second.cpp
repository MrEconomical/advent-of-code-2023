#include <fstream>
#include <iostream>
#include <istream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::stringstream, std::vector;

const long long MAX_LLONG = std::numeric_limits<long long>::max();
const size_t MAX_LEN = std::numeric_limits<std::streamsize>::max();

struct SeedRange {
    long long start;
    long long len;
};

struct Range {
    long long source;
    long long dest;
    long long len;
};

istream* get_input_stream() {
    return new ifstream("seeds.txt");
}

vector<SeedRange> parse_seeds(const string& line) {
    stringstream line_stream(line);
    line_stream.ignore(MAX_LEN, ' ');

    vector<SeedRange> seeds;
    string start, len;
    while (std::getline(line_stream, start, ' ')
        && std::getline(line_stream, len, ' ')) {
        SeedRange range = SeedRange{std::stoll(start), std::stoll(len)};
        seeds.push_back(range);
    }

    return seeds;
}

Range parse_range(const string& line) {
    stringstream line_stream(line);
    Range range;
    line_stream >> range.dest >> range.source >> range.len;
    return range;
}

long long get_seed_location(const vector<vector<Range>>& mappings, long long seed) {
    for (const vector<Range>& mapping : mappings) {
        for (Range range : mapping) {
            if (seed >= range.source && seed < range.source + range.len) {
                long long offset = seed - range.source;
                seed = range.dest + offset;
                break;
            }
        }
    }
    return seed;
}

int main() {
    istream& input = *get_input_stream();

    string line;
    std::getline(input, line);
    vector<SeedRange> seeds = parse_seeds(line);
    input.ignore(MAX_LEN, '\n');

    vector<vector<Range>> mappings;
    while (std::getline(input, line)) {
        vector<Range> mapping;
        while (std::getline(input, line) && line != "") {
            mapping.push_back(parse_range(line));
        }
        mappings.push_back(mapping);
    }

    long long min_location{MAX_LLONG};
    for (SeedRange range : seeds) {
        for (long long s = 0; s < range.len; s ++) {
            long long location = get_seed_location(mappings, range.start + s);
            if (location < min_location) {
                min_location = location;
            }
        }
        std::cout << "Finished range: " << range.start << " " << range.len << "\n";
    }

    std::cout << "Minimum location: " << min_location << "\n";
}