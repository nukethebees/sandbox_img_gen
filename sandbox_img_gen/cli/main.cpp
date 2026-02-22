#include <sandbox_img_gen/shapes.hpp>

#include <Magick++.h>

#include <cstdint>
#include <cstddef>

namespace mgk = Magick;

static void draw_circle() {
    constexpr std::size_t width{1024uz};
    constexpr std::size_t height{width};
    constexpr std::int64_t offset{0};

    mgk::Geometry const geometry{width, height, offset, offset};
    mgk::ColorRGB const colour{1.f, 1.f, 1.f, 1.f};
    mgk::Image image{geometry, colour};

    auto const circle{sbx::draw_circle(width, height, 0.1)};

    image.draw(circle);
    image.write("circle.png");
}

int main(int /*argc*/, char** argv) {
    mgk::MagickPlusPlusGenesis genesis{*argv};

    static_assert(sizeof(mgk::Quantum) == sizeof(float));

    draw_circle();

    return 0;
}
