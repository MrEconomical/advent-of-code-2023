#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::vector;

struct Play {
    string hand;
    int bid;
};

istream* get_input_stream() {
    return new ifstream("camel.txt");
}

int get_rank(char card) {
    if ('2' <= card && card <= '9') {
        return card - '0';
    }
    switch (card) {
        case 'T':
            return 10;
        case 'J':
            return 11;
        case 'Q':
            return 12;
        case 'K':
            return 13;
        case 'A':
            return 14;
    }
    return 0;
}

bool compare_tie(const string& first, const string& second) {
    for (size_t c = 0; c < first.size(); c ++) {
        if (get_rank(first[c]) > get_rank(second[c])) {
            return true;
        } else if (get_rank(first[c]) < get_rank(second[c])) {
            return false;
        }
    }
    return true;
}

int get_hand_type(const string& hand) {
    int card_counts[15];
    for (int c = 0; c < 15; c ++) {
        card_counts[c] = 0;
    }
    for (char card : hand) {
        card_counts[get_rank(card)] ++;
    }

    int num_triple{0};
    int num_pair{0};
    for (int c = 2; c <= 14; c ++) {
        if (card_counts[c] == 5) {
            return 6;
        } else if (card_counts[c] == 4) {
            return 5;
        } else if (card_counts[c] == 3) {
            num_triple ++;
        } else if (card_counts[c] == 2) {
            num_pair ++;
        }
    }

    if (num_triple == 1 && num_pair == 1) {
        return 4;
    } else if (num_triple == 1) {
        return 3;
    } else if (num_pair == 2) {
        return 2;
    } else if (num_pair == 1) {
        return 1;
    }
    return 0;
}

bool compare_hands(const string& first, const string& second) {
    int first_type = get_hand_type(first);
    int second_type = get_hand_type(second);
    if (first_type != second_type) {
        return first_type > second_type;
    }
    return compare_tie(first, second);
}

int main() {
    istream& input = *get_input_stream();

    vector<Play> plays;
    Play play;
    while (input >> play.hand >> play.bid) {
        plays.push_back(play);
    }

    std::sort(
        plays.begin(),
        plays.end(),
        [](const Play& a, const Play& b) {
            return compare_hands(a.hand, b.hand);
        }
    );

    int total{0};
    for (int p = 0; p < plays.size(); p ++) {
        total += plays[p].bid * (plays.size() - p);
    }

    std::cout << "Total winnings: " << total << "\n";
}