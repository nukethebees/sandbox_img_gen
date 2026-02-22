#include <Magick++.h>

#include <print>

int main(int /*argc*/, char** argv) {
    Magick::MagickPlusPlusGenesis genesis{*argv};

    std::print("Hello, world!");
    return 0;
}
