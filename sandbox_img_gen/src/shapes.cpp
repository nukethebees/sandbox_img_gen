#include <sandbox_img_gen/shapes.hpp>

#include <Magick++.h>

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <print>

namespace mgk = Magick;

namespace sbx {
auto CircleDrawer::draw_relative(double const w_pos,
                                 double const h_pos,
                                 double const size_proportion) const -> mgk::DrawableCircle {

    auto const circle_w{img_w() * w_pos};
    auto const circle_h{img_h() * h_pos};
    auto const circle_perim_x{circle_w + img_w() * size_proportion};
    auto const circle_perim_y{circle_h + img_h() * size_proportion};

    return mgk::DrawableCircle{circle_w, circle_h, circle_perim_x, circle_perim_y};
}
auto CircleDrawer::draw_centre(double const size_proportion) const -> mgk::DrawableCircle {
    return draw_relative(0.5, 0.5, size_proportion);
}
auto CircleDrawer::draw_centred_grid(std::size_t const width_divisions,
                                     std::size_t const height_divisions,
                                     double const size_proportion) const
    -> std::vector<Magick::DrawableCircle> {
    std::vector<Magick::DrawableCircle> out;

    if (width_divisions < 1) {
        throw std::invalid_argument("Width divisions < 1");
    }
    if (height_divisions < 1) {
        throw std::invalid_argument("Height divisions < 1");
    }

    auto const dw{img_w() / (static_cast<double>(width_divisions) + 1.0)};
    auto const dh{img_h() / (static_cast<double>(height_divisions) + 1.0)};

    for (std::size_t iw{0}; iw < width_divisions; ++iw) {
        for (std::size_t ih{0}; ih < height_divisions; ++ih) {
            auto const x{dw * static_cast<double>(iw + 1)};
            auto const y{dh * static_cast<double>(ih + 1)};

            auto const perim_x{x + img_w() * size_proportion};
            auto const perim_y{y + img_h() * size_proportion};

            out.emplace_back(x, y, perim_x, perim_y);
        }
    }

    return out;
}
}
