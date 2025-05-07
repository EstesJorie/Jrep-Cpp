#include <iostream>
#include <fstream>
#include <regex>
#include <string>

void printHighlighted(const std::string& line, const std::smatch& match) {
    std::cout << line.substr(0, match.position());
    std::cout << "\033[1;31m" << match.str() << "\033[0m";
    std::cout << line.substr(match.position() + match.length());
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " pattern [file]" << std::endl;
        return 1;
    }

    std::string pattern = argv[1];
    std::istream* input = &std::cin;
    std::ifstream file;

    if (argc > 2) {
        file.open(argv[2]);
        if (!file) {
            std::perror("fopen");
            return 1;
        }
        input = &file;
    }

    std::regex regex;
    try {
        regex = std::regex(pattern, std::regex_constants::icase);
    } catch (const std::regex_error& e) {
        std::cerr << "Could not compile regex: " << e.what() << std::endl;
        return 1;
    }

    std::string line;
    int lineNum = 0;
    while (std::getline(*input, line)) {
        lineNum++;
        std::smatch match;
        if (std::regex_search(line, match, regex)) {
            std::cout << std::setw(4) << lineNum << ": ";
            printHighlighted(line, match);
            std::cout << std::endl;
        }
    }

    return 0;
}

