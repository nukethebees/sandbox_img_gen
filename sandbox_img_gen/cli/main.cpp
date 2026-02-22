#include <sandbox_img_gen/shapes.hpp>

#include <Magick++.h>

#include <cstdint>
#include <cstddef>
#include <print>

namespace mgk = Magick;

namespace sbx {
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

    auto const circles{drawer.draw_centred_rect_grid(2u, 2u, 0.05)};
    for (auto const& c : circles) {
        image.draw(c);
    }

    image.write("grid_image_0.png");
}

static void
    draw_rect_die(std::size_t const w_div, std::size_t const h_div, double const proportion) {
    constexpr std::size_t width{1024uz};
    constexpr std::size_t height{width};
    auto image{blank_image(width, height)};

    sbx::CircleDrawer drawer{width, height};

    auto const circles{drawer.draw_centred_rect_grid(w_div, h_div, proportion)};
    for (auto const& c : circles) {
        image.draw(c);
    }

    image.write(std::format("die_{}.png", w_div * h_div));
}
static void draw_x_die(std::size_t const back, std::size_t const fwd, double const proportion) {
    constexpr std::size_t width{1024uz};
    constexpr std::size_t height{width};
    auto image{blank_image(width, height)};

    sbx::CircleDrawer drawer{width, height};

    auto draw_line{[&image, &drawer](std::size_t const n,
                                     DiagonalLineDirection const direction,
                                     double const proportion) -> void {
        if (!n) {
            return;
        }

        auto const circles{drawer.draw_centred_diagonal_line_grid(n, direction, proportion)};
        for (auto const& c : circles) {
            image.draw(c);
        }
    }};

    draw_line(fwd, DiagonalLineDirection::forward, proportion);
    draw_line(back, DiagonalLineDirection::backward, proportion);

    auto num{fwd + back};
    if ((fwd % 2 != 0) && (back % 2 != 0)) {
        // Middle dot overlaps
        num--;
    }

    image.write(std::format("die_{}.png", num));
}
}

int main(int /*argc*/, char** argv) {
    mgk::MagickPlusPlusGenesis genesis{*argv};

    static_assert(sizeof(mgk::Quantum) == sizeof(float));

    using namespace sbx;
    draw_circle();
    draw_grid();

    constexpr double prop{0.05};

    draw_rect_die(1, 1, prop);
    draw_x_die(0u, 2u, prop);
    draw_x_die(3u, 0u, prop);
    draw_rect_die(2, 2, prop);
    draw_x_die(3u, 3u, prop);
    draw_rect_die(3, 2, prop);

    return 0;
}
