#include <sandbox_img_gen/shapes.hpp>

#include <Magick++.h>

#include <cstdint>
#include <cstddef>

namespace mgk = Magick;

namespace sbx {
auto draw_circle(Dimension const img_w, Dimension const img_h, double proportion)
    -> mgk::DrawableCircle {

    auto const circle_w{img_w / 2.0};
    auto const circle_h{img_h / 2.0};
    auto const circle_perim_x{circle_w + img_w * proportion};
    auto const circle_perim_y{circle_h + img_h * proportion};

    return mgk::DrawableCircle{circle_w, circle_h, circle_perim_x, circle_perim_y};
}
}
