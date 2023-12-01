#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>


std::vector<std::string> split(std::string s, char delimeter = ' ') {
    std::istringstream iss(s);
    std::vector<std::string> tokens;
    std::string token;

    // Use a while loop to extract space-separated tokens
    //while (iss >> token) {
    while (std::getline(iss, token, delimeter)) {
        tokens.push_back(token);       
    }
    return tokens;
}

// Function to split a string using a custom delimiter
std::vector<std::string> splitString(const std::string& input, char delimiter = ' ') {
    std::vector<std::string> tokens;
    std::string token;

    for (char c : input) {
        if (c == delimiter) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += c;
        }
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}
