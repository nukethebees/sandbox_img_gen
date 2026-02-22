#include <Magick++.h>

#include <cstddef>
#include <vector>

namespace sbx {
class CircleDrawer {
  public:
    CircleDrawer() = delete;
    CircleDrawer(double img_w, double img_h)
        : img_w_{img_w}
        , img_h_{img_h} {}

    auto img_w() const { return img_w_; }
    auto img_h() const { return img_h_; }

    auto draw_relative(double const w_pos, double const h_pos, double const size_proportion) const
        -> Magick::DrawableCircle;
    auto draw_centre(double const size_proportion) const -> Magick::DrawableCircle;
    auto draw_centred_rect_grid(std::size_t const width_divisions,
                                std::size_t const height_divisions,
                                double const size_proportion) const
        -> std::vector<Magick::DrawableCircle>;
  private:
    double img_w_{0.0};
    double img_h_{0.0};
};
}
