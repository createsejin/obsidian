//#include "study/study08.h"
//#include "study/study09.h"
#include "study/study19.h"
#include "lib/CLI11.hpp"
#include <iostream>

using namespace std;

int main000(const int argc, char* argv[])
{
    std::cout << "Program start" << std::endl;
    CLI::App app{"App description"};

    std::string filename = "default";
    app.add_option("-f,--file", filename, "A help string");

    CLI11_PARSE(app, argc, argv);
    std::cout << "Parsed filename: " << filename << std::endl;
    return 0;
}

int main001(const int argc, char* argv[])
{
    std::cout << "Program start" << std::endl;
    //CLI::App app{"App description"};

    std::string input;
    cout << "cmd> " << std::flush;
    std::getline(std::cin, input);

    if (const auto pos = input.find("cmd>");
        pos != std::string::npos) {
        input.erase(pos, 5);
    }
    cout << "input = |" << input << "|" << endl;
    // std::string filename = "default";
    // app.add_option("-f,--file", filename, "A help string");
    //
    // CLI11_PARSE(app, argc, argv);
    // std::cout << "Parsed filename: " << filename << std::endl;
    return 0;
}

int main(const int argc, char* argv[]) {
    std::cout << "Program start" << std::endl;
    study19::study01::study004();
}
