#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::stringstream, std::vector;

istream* get_input_stream() {
    return new ifstream("scratchcards.txt");
}

vector<int> parse_nums(const string& str) {
    vector<int> nums;
    stringstream str_stream(str);
    string token;
    while (std::getline(str_stream, token, ' ')) {
        if (token != "") {
            nums.push_back(std::stoi(token));
        }
    }
    return nums;
}

int get_card_points(const string& card) {
    size_t index = card.find("|");
    vector<int> targets = parse_nums(card.substr(0, index));
    vector<int> nums = parse_nums(card.substr(index + 1));

    int overlaps{0};
    for (int target : targets) {
        for (int num : nums) {
            if (num == target) {
                overlaps ++;
            }
        }
    }

    if (overlaps > 0) {
        return std::pow(2, overlaps - 1);
    }
    return 0;
}

int main() {
    istream& input = *get_input_stream();

    int total{0};
    string line;
    while (std::getline(input, line)) {
        size_t index = line.find(": ");
        int points = get_card_points(line.substr(index + 2));
        total += points;
    }

    std::cout << "Total points: " << total << "\n";
}