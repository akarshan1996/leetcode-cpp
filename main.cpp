#include <iostream>
#include <cstring>
#include <map>

void run0005();
void run0042();
void run0053();
void run0138();
void run0151();
void run0165();
void run0200();
void run0297();
void run0315();
void run0560();
void run0621();
void run0973();

int main(const int argc, const char *const argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number>" << std::endl;
        return 1;
    }

    const std::string number(argv[1]);

    static const std::map<const std::string, void (*const)()> runMap = {
            {"5",   run0005},
            {"42",  run0042},
            {"53",  run0053},
            {"138", run0138},
            {"151", run0151},
            {"165", run0165},
            {"200", run0200},
            {"297", run0297},
            {"315", run0315},
            {"560", run0560},
            {"621", run0621},
            {"973", run0973},
    };

    if (runMap.find(number) == runMap.end()) {
        std::cerr << "Not found: " << argv[1] << std::endl;
        return 2;
    }

    void (*const run)() = runMap.at(number);
    run();

    return 0;
}
