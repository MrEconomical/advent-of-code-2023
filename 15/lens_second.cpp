#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::stringstream, std::vector;

const int NUM_BOXES = 256;
const int HASH_FACTOR = 17;

struct Lens {
    string label;
    int len;
};

istream* get_input_stream() {
    return new ifstream("lens.txt");
}

int calc_hash(const string& step) {
    int hash{0};
    for (char c : step) {
        hash += c;
        hash = (hash * HASH_FACTOR) % NUM_BOXES;
    }
    return hash;
}

void remove_lens(vector<vector<Lens>>& lenses, const string& label) {
    int box = calc_hash(label);
    for (size_t l = 0; l < lenses[box].size(); l ++) {
        if (lenses[box][l].label == label) {
            lenses[box].erase(lenses[box].begin() + l);
            return;
        }
    }
}

void add_lens(vector<vector<Lens>>& lenses, const string& label, int len) {
    int box = calc_hash(label);
    for (size_t l = 0; l < lenses[box].size(); l ++) {
        if (lenses[box][l].label == label) {
            lenses[box][l].len = len;
            return;
        }
    }
    lenses[box].push_back(Lens{label, len});
}

int main() {
    istream& input = *get_input_stream();

    string line;
    std::getline(input, line);
    stringstream line_stream(line);

    vector<vector<Lens>> lenses(NUM_BOXES);
    string step;
    while (std::getline(line_stream, step, ',')) {
        if (step[step.size() - 1] == '-') {
            string label = step.substr(0, step.size() - 1);
            remove_lens(lenses, label);
        } else {
            size_t index = step.find('=');
            string label = step.substr(0, index);
            int len = std::stoi(step.substr(index + 1));
            add_lens(lenses, label, len);
        }
    }

    int total{0};
    for (int b = 0; b < NUM_BOXES; b ++) {
        for (int l = 0; l < lenses[b].size(); l ++) {
            total += (b + 1) * (l + 1) * lenses[b][l].len;
        }
    }

    std::cout << "Total: " << total << "\n";
}