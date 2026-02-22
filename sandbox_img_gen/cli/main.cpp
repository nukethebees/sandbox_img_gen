#include <Magick++.h>

#include <cstdint>
#include <cstddef>

namespace mgk = Magick;

static void draw_circle() {
    constexpr std::size_t width{1024uz};
    constexpr std::size_t height{width};
    constexpr std::int64_t offset{0};

    constexpr auto width_d{static_cast<double>(width)};
    constexpr auto height_d{static_cast<double>(height)};

    mgk::Geometry const geometry{width, height, offset, offset};
    mgk::ColorRGB const colour{1.f, 1.f, 1.f, 1.f};
    mgk::Image image{geometry, colour};

    constexpr double circle_w{width_d / 2};
    constexpr double circle_h{height_d / 2};
    constexpr double circle_perim_x{circle_w + width_d * 0.1};
    constexpr double circle_perim_y{circle_h + height_d * 0.1};
    mgk::DrawableCircle const circle{circle_w, circle_h, circle_perim_x, circle_perim_y};

    image.draw(circle);
    image.write("circle.png");
}

int main(int /*argc*/, char** argv) {
    mgk::MagickPlusPlusGenesis genesis{*argv};

    static_assert(sizeof(mgk::Quantum) == sizeof(float));

    draw_circle();

    return 0;
}
