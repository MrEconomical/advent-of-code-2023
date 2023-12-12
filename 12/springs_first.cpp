#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::stringstream, std::vector;

struct Record {
    string row;
    int missing;
    vector<int> groups;
};

istream* get_input_stream() {
    return new ifstream("springs.txt");
}

int count_missing(const string& row) {
    int missing{0};
    for (char c : row) {
        if (c == '?') {
            missing ++;
        }
    }
    return missing;
}

void parse_groups(vector<int>& groups, const string& list) {
    stringstream list_stream(list);
    string num;
    while (std::getline(list_stream, num, ',')) {
        groups.push_back(std::stoi(num));
    }
}

Record parse_record(const string& line) {
    Record record;
    size_t index = line.find(" ");
    record.row = line.substr(0, index);
    record.missing = count_missing(record.row);
    parse_groups(record.groups, line.substr(index + 1));
    return record;
}

bool check_groups(const string& arrangement, const vector<int>& groups) {
    int size{0};
    size_t group_index{0};
    for (char s : arrangement) {
        if (s == '#') {
            size ++;
        } else if (size > 0) {
            if (group_index >= groups.size() || size != groups[group_index]) {
                return false;
            }
            size = 0;
            group_index ++;
        }
    }

    if (size > 0) {
        if (group_index != groups.size() - 1 || size != groups[group_index]) {
            return false;
        }
        return true;
    }
    return group_index == groups.size();
}

bool check_arrangement(const Record& record, int order) {
    string arrangement(record.row);
    int order_shift{0};
    for (size_t s = 0; s < arrangement.size(); s ++) {
        if (arrangement[s] == '?') {
            int status = (order >> order_shift) & 1;
            arrangement[s] = status == 0 ? '.' : '#';
            order_shift ++;
        }
    }
    return check_groups(arrangement, record.groups);
}

int count_arrangements(const Record& record) {
    if (record.missing == 0) {
        return 1;
    }

    int arrangements{0};
    int limit = std::pow(2, record.missing);
    for (int a = 0; a < limit; a ++) {
        if (check_arrangement(record, a)) {
            arrangements ++;
        }
    }

    return arrangements;
}

int main() {
    istream& input = *get_input_stream();

    vector<Record> records;
    string line;
    while (std::getline(input, line)) {
        Record record = parse_record(line);
        records.push_back(record);
    }

    int total{0};
    for (const Record& record : records) {
        total += count_arrangements(record);
    }

    std::cout << "Total arrangements: " << total << "\n";
}