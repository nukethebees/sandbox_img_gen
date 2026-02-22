#include <Magick++.h>

#include <cstddef>

namespace sbx {
class CircleDrawer {
  public:
    CircleDrawer() = delete;
    CircleDrawer(double img_w, double img_h)
        : img_w_{img_w}
        , img_h_{img_h} {}

    auto img_w() const { return img_w_; }
    auto img_h() const { return img_h_; }

    auto draw_centre(double const proportion) const -> Magick::DrawableCircle;
  private:
    double img_w_{0.0};
    double img_h_{0.0};
};
}
