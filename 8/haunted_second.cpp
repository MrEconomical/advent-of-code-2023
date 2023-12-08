#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <limits>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using std::ifstream, std::istream;
using std::pair, std::string, std::unordered_map, std::vector;

const size_t MAX_STREAM_LEN = std::numeric_limits<std::streamsize>::max();
const size_t KEY_LEN = 3;

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

int get_cycle_len(
    const unordered_map<string, Node>& nodes,
    const string& sequence,
    string node
) {
    int moves{0};
    while (node[KEY_LEN - 1] != 'Z') {
        for (char c : sequence) {
            if (c == 'L') {
                node = nodes.at(node).left;
            } else {
                node = nodes.at(node).right;
            }
        }
        moves += sequence.size();
    }
    return moves;
}

long long gcd(long long a, long long b) {
    if (a == 0) {
        return b;
    } else if (b == 0) {
        return a;
    }
    if (a == b) {
        return a;
    }

    if (a > b) {
        return gcd(a - b, b);
    }
    return gcd(a, b - a);
}

long long lcm(long long a, long long b) {
    return a * b / gcd(a, b);
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

    vector<int> cycle_lens;
    for (const pair<string, Node>& entry : nodes) {
        if (entry.first[KEY_LEN - 1] == 'A') {
            int cycle_len = get_cycle_len(nodes, sequence, entry.first);
            cycle_lens.push_back(cycle_len);
        }
    }

    std::cout << "Cycle lengths: ";
    for (int len : cycle_lens) {
        std::cout << len << " ";
    }
    std::cout << "\n";

    long long moves = cycle_lens[0];
    for (size_t l = 1; l < cycle_lens.size(); l ++) {
        moves = lcm(moves, cycle_lens[l]);
    }
    std::cout << "Total moves: " << moves << "\n";
}