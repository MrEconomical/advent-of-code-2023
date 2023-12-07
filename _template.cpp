#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <vector>

using std::ifstream, std::istream;
using std::string, std::vector;

istream* get_input_stream() {
    return new ifstream("input.txt");
}

int main() {
    istream& input = *get_input_stream();
}