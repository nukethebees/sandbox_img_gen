#include <Magick++.h>

#include <cstdint>
#include <cstddef>

namespace mgk = Magick;

namespace sbx {
auto draw_circle(std::size_t const width_i, std::size_t const height_i) -> mgk::DrawableCircle {
    auto const width_fp{static_cast<double>(width_i)};
    auto const height_fp{static_cast<double>(height_i)};

    auto const circle_w{width_fp / 2};
    auto const circle_h{height_fp / 2};
    auto const circle_perim_x{circle_w + width_fp * 0.1};
    auto const circle_perim_y{circle_h + height_fp * 0.1};

    return mgk::DrawableCircle{circle_w, circle_h, circle_perim_x, circle_perim_y};
}
}
