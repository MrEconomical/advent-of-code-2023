#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::stringstream, std::vector;

const int NUM_RED = 12;
const int NUM_GREEN = 13;
const int NUM_BLUE = 14;

struct RoundValues {
    int red;
    int green;
    int blue;
};

istream* get_input_stream() {
    return new ifstream("cube.txt");
}

RoundValues parse_game_round(const string& round) {
    stringstream round_stream(round);
    RoundValues round_values{0, 0, 0};
    string draw;

    while (std::getline(round_stream, draw, ',')) {
        size_t space_index;
        int count;
        string color;

        if (draw[0] == ' ') {
            space_index = draw.find(' ', 1);
            count = std::stoi(draw.substr(1, space_index));
        } else {
            space_index = draw.find(' ');
            count = std::stoi(draw.substr(0, space_index));
        }
        color = draw.substr(space_index + 1);

        if (color == "red") {
            round_values.red = count;
        } else if (color == "green") {
            round_values.green = count;
        } else if (color == "blue") {
            round_values.blue = count;
        }
    }

    return round_values;
}

bool check_possible(const string& game) {
    stringstream game_stream(game);
    string round;
    while (std::getline(game_stream, round, ';')) {
        RoundValues round_values = parse_game_round(round);
        if (round_values.red > NUM_RED
            || round_values.green > NUM_GREEN
            || round_values.blue > NUM_BLUE) {
            return false;
        }
    }
    return true;
}

int main() {
    istream& input = *get_input_stream();

    int total{0};
    int game_num{1};
    string line;
    while (std::getline(input, line)) {
        size_t index = line.find(": ");
        if (check_possible(line.substr(index + 2))) {
            total += game_num;
        }
        game_num ++;
    }

    std::cout << "Total value: " << total << "\n";
}