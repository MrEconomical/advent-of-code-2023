#include <fstream>
#include <iostream>
#include <istream>

using std::ifstream, std::istream;

istream* get_input_stream() {
    return new ifstream("input.txt");
}

int main() {
    istream& input = *get_input_stream();
}