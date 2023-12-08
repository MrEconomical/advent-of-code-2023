#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::unordered_map, std::vector;

const size_t MAX_STREAM_LEN = std::numeric_limits<std::streamsize>::max();
const size_t KEY_LEN = 3;
const string START_NODE = "AAA";
const string END_NODE = "ZZZ";

struct Node {
    string key;
    string left;
    string right;
};

istream* get_input_stream() {
    return new ifstream("haunted.txt");
}

Node parse_node(const string& line) {
    Node node;
    node.key = line.substr(0, KEY_LEN);
    node.left = line.substr(KEY_LEN + 4, KEY_LEN);
    node.right = line.substr(KEY_LEN + 4 + KEY_LEN + 2, KEY_LEN);
    return node;
}

int main() {
    istream& input = *get_input_stream();

    string sequence;
    input >> sequence;
    input.ignore(MAX_STREAM_LEN, '\n');
    input.ignore(MAX_STREAM_LEN, '\n');

    unordered_map<string, Node> nodes;
    string line;
    while (std::getline(input, line)) {
        Node node = parse_node(line);
        nodes[node.key] = node;
    }

    int moves{0};
    string current = START_NODE;
    while (current != END_NODE) {
        for (char c : sequence) {
            if (c == 'L') {
                current = nodes[current].left;
            } else {
                current = nodes[current].right;
            }
        }
        moves += sequence.size();
    }

    std::cout << "Total moves: " << moves << "\n";
}