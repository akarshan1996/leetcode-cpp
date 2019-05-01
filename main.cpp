#include <iostream>
#include <cstring>

void run0042();

int main(const int argc, const char *const argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number>" << std::endl;
        return 1;
    }

    if (std::strcmp(argv[1], "42") == 0) {
        run0042();
    } else {
        std::cerr << "Not found: " << argv[1] << std::endl;
        return 2;
    }

    return 0;
}
