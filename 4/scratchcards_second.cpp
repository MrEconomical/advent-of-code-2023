#include <fstream>
#include <iostream>
#include <istream>
#include <numeric>
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

int get_card_overlaps(const string& card) {
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

    return overlaps;
}

int main() {
    istream& input = *get_input_stream();

    vector<string> cards;
    string line;
    while (std::getline(input, line)) {
        cards.push_back(line);
    }

    vector<int> copies(cards.size(), 1);
    for (int c = 0; c < cards.size(); c ++) {
        size_t index = cards[c].find(": ");
        int overlaps = get_card_overlaps(cards[c].substr(index + 2));
        for (int n = 1; n <= overlaps; n ++) {
            copies[c + n] += copies[c];
        }
    }

    int total = std::accumulate(copies.begin(), copies.end(), 0);
    std::cout << "Total cards: " << total << "\n";
}