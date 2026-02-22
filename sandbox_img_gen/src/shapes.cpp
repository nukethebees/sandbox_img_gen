#include <sandbox_img_gen/shapes.hpp>

#include <Magick++.h>

#include <cstdint>
#include <cstddef>

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
}
