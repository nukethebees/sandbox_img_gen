#include "dimension.hpp"

#include <Magick++.h>

#include <cstddef>

namespace sbx {
auto draw_circle(Dimension width, Dimension height, double proportion) -> Magick::DrawableCircle;
}
