#include <iostream>
#include <cstring>
#include <map>

void run0005();
void run0023();
void run0033();
void run0042();
void run0053();
void run0054();
void run0103();
void run0138();
void run0151();
void run0165();
void run0200();
void run0238();
void run0289();
void run0297();
void run0315();
void run0427();
void run0560();
void run0621();
void run0741();
void run0973();

int main(const int argc, const char *const argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number>" << std::endl;
        return 1;
    }

    const std::string number(argv[1]);

    static const std::map<const std::string, void (*const)()> runMap = {
            {"5",   run0005},
            {"23",  run0023},
            {"33",  run0033},
            {"42",  run0042},
            {"53",  run0053},
            {"54",  run0054},
            {"103", run0103},
            {"138", run0138},
            {"151", run0151},
            {"165", run0165},
            {"200", run0200},
            {"238", run0238},
            {"289", run0289},
            {"297", run0297},
            {"315", run0315},
            {"427", run0427},
            {"560", run0560},
            {"621", run0621},
            {"741", run0741},
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
