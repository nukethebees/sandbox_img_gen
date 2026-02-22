#include <sandbox_img_gen/shapes.hpp>

#include <Magick++.h>

#include <array>
#include <cstdint>
#include <cstddef>
#include <print>
#include <string_view>

namespace mgk = Magick;

namespace sbx {
class ImgGenerator {
  public:
    ImgGenerator() = delete;
    ImgGenerator(std::size_t width, std::size_t height)
        : width_{width}
        , height_{height}
        , circle_drawer_{static_cast<double>(width_), static_cast<double>(height_)} {}
    auto blank_image() const {
        constexpr std::int64_t offset{0};

        mgk::Geometry const geometry{width_, height_, offset, offset};
        mgk::ColorRGB const colour{1.f, 1.f, 1.f, 1.f};
        mgk::Image image{geometry, colour};

        return image;
    }
    void draw_circle() {
        auto image{blank_image()};

        auto const circle{circle_drawer_.draw_centre(0.1)};
        image.draw(circle);
        write(image, "circle");
    }
    void draw_grid() {
        auto image{blank_image()};

        auto const circles{circle_drawer_.draw_centred_rect_grid(2u, 2u, 0.05)};
        for (auto const& c : circles) {
            image.draw(c);
        }

        write(image, "grid_image_0");
    }

    void draw_rect_die(std::size_t const w_div, std::size_t const h_div, double const proportion) {
        auto image{blank_image()};

        auto const circles{circle_drawer_.draw_centred_rect_grid(w_div, h_div, proportion)};
        for (auto const& c : circles) {
            image.draw(c);
        }

        write(image, std::format("die_{}", w_div * h_div));
    }
    void draw_x_die(std::size_t const back, std::size_t const fwd, double const proportion) {
        auto image{blank_image()};

        auto draw_line{[&](std::size_t const n,
                           DiagonalLineDirection const direction,
                           double const proportion) -> void {
            if (!n) {
                return;
            }

            auto const circles{
                circle_drawer_.draw_centred_diagonal_line_grid(n, direction, proportion)};
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

        write(image, std::format("die_{}", num));
    }
    void write(Magick::Image& image, std::string_view name) const {
        auto const file_name{std::format("{}_{}x{}.png", name, width_, height_)};
        image.write(file_name);
    }
  private:
    std::size_t width_{0u};
    std::size_t height_{0u};
    sbx::CircleDrawer circle_drawer_;
};

}

int main(int /*argc*/, char** argv) {
    mgk::MagickPlusPlusGenesis genesis{*argv};

    static_assert(sizeof(mgk::Quantum) == sizeof(float));

    using namespace sbx;

    constexpr double prop{0.05};
    std::array<std::size_t, 4> muls{1u, 2u, 4u, 8u};
    for (auto mul : muls) {
        auto const dim{1024u * mul};
        ImgGenerator ig{dim, dim};

        ig.draw_circle();
        ig.draw_grid();

        ig.draw_rect_die(1, 1, prop);
        ig.draw_x_die(0u, 2u, prop);
        ig.draw_x_die(3u, 0u, prop);
        ig.draw_rect_die(2, 2, prop);
        ig.draw_x_die(3u, 3u, prop);
        ig.draw_rect_die(3, 2, prop);
    }

    return 0;
}
