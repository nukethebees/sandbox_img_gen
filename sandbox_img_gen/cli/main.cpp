#include <sandbox_img_gen/shapes.hpp>

#include <Magick++.h>

#include <cstdint>
#include <cstddef>
#include <print>

namespace mgk = Magick;

static auto blank_image(std::size_t width, std::size_t height) {
    constexpr std::int64_t offset{0};

    mgk::Geometry const geometry{width, height, offset, offset};
    mgk::ColorRGB const colour{1.f, 1.f, 1.f, 1.f};
    mgk::Image image{geometry, colour};

    return image;
}

static void draw_circle() {
    constexpr std::size_t width{1024uz};
    constexpr std::size_t height{width};
    auto image{blank_image(width, height)};

    sbx::CircleDrawer drawer{width, height};
    auto const circle{drawer.draw_centre(0.1)};
    image.draw(circle);
    image.write("circle.png");
}
static void draw_grid() {
    constexpr std::size_t width{1024uz};
    constexpr std::size_t height{width};
    auto image{blank_image(width, height)};

    sbx::CircleDrawer drawer{width, height};

    auto const circles{drawer.draw_centred_grid(2u, 2u, 0.05)};
    for (auto const& c : circles) {
        image.draw(c);
    }

    image.write("grid_image_0.png");
}

int main(int /*argc*/, char** argv) {
    mgk::MagickPlusPlusGenesis genesis{*argv};

    static_assert(sizeof(mgk::Quantum) == sizeof(float));

    draw_circle();
    draw_grid();

    return 0;
}
