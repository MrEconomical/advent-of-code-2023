#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::stringstream, std::vector;

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

int get_power(const string& game) {
    RoundValues max_values{0, 0, 0};
    stringstream game_stream(game);
    string round;

    while (std::getline(game_stream, round, ';')) {
        RoundValues round_values = parse_game_round(round);
        max_values.red = std::max(max_values.red, round_values.red);
        max_values.green = std::max(max_values.green, round_values.green);
        max_values.blue = std::max(max_values.blue, round_values.blue);
    }

    return max_values.red * max_values.green * max_values.blue;
}

int main() {
    istream& input = *get_input_stream();

    int total{0};
    string line;
    while (std::getline(input, line)) {
        size_t index = line.find(": ");
        int power = get_power(line.substr(index + 2));
        total += power;
    }

    std::cout << "Total power: " << total << "\n";
}