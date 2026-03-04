#include <float.h> // Needed first to fix TBB errors

#include <sandbox_img_gen/shapes.hpp>
#include <sandbox_img_gen/static_pmr_vector.hpp>

#include <Magick++.h>

#include <oneapi/tbb.h>

#include <array>
#include <cstdint>
#include <cstddef>
#include <filesystem>
#include <functional>
#include <string_view>
#include <format>

namespace mgk = Magick;

namespace sbx {
namespace fs = std::filesystem;

class ImgGenerator {
  public:
    ImgGenerator() = delete;
    ImgGenerator(std::size_t width, std::size_t height)
        : width_{width}
        , height_{height}
        , circle_drawer_{static_cast<double>(width_), static_cast<double>(height_)} {}

    void create_directories() {
        fs::create_directories("dice");
        fs::create_directories("squares");
        fs::create_directories("misc");
    }

    auto blank_image(mgk::ColorRGB colour) const {
        constexpr std::int64_t offset{0};

        mgk::Geometry const geometry{width_, height_, offset, offset};
        mgk::Image image{geometry, colour};

        return image;
    }
    auto blank_image() const {
        mgk::ColorRGB const colour{1.f, 1.f, 1.f, 1.f};
        return blank_image(colour);
    }
    void draw_circle() const {
        auto image{blank_image()};

        auto const circle{circle_drawer_.draw_centre(0.1)};
        image.draw(circle);
        write(image, "misc/circle");
    }
    void draw_grid() const {
        auto image{blank_image()};

        auto const circles{circle_drawer_.draw_centred_rect_grid(2u, 2u, 0.05)};
        for (auto const& c : circles) {
            image.draw(c);
        }

        write(image, "misc/grid_image_0");
    }

    void draw_rect_die(std::size_t const w_div,
                       std::size_t const h_div,
                       double const proportion) const {
        auto image{blank_image()};

        auto const circles{circle_drawer_.draw_centred_rect_grid(w_div, h_div, proportion)};
        for (auto const& c : circles) {
            image.draw(c);
        }

        write(image, std::format("dice/die_{}", w_div * h_div));
    }
    void draw_x_die(std::size_t const back, std::size_t const fwd, double const proportion) const {
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

        write(image, std::format("dice/die_{}", num));
    }
    void draw_square(double rel_size) {
        mgk::ColorRGB const red{1.f, 0.f, 0.f, 1.f};
        auto image{blank_image(red)};

        auto const i_w{static_cast<double>(width_)};
        auto const i_h{static_cast<double>(height_)};

        auto const sq_side{i_w * rel_size};

        auto const x0{(i_w - sq_side) / 2.0};
        auto const y0{(i_h - sq_side) / 2.0};

        mgk::DrawableList draw_list;
        draw_list.push_back(mgk::DrawableStrokeColor("none"));
        draw_list.push_back(mgk::DrawableFillColor("green"));
        draw_list.push_back(mgk::DrawableRectangle(x0, y0, x0 + sq_side, y0 + sq_side));
        image.draw(draw_list);

        auto name{std::format("squares/square_{:.2f}", rel_size)};
        for (char& c : name) {
            if (c == '.') {
                c = 'p';
            }
        }
        write(image, name);
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

    constexpr double prop{0.05};
    constexpr std::array<std::size_t, 4> muls{{1u, 2u, 4u, 8u}};

    sbx::StaticPmrVector<sbx::ImgGenerator, muls.size()> igs_vec;
    auto& igs{igs_vec.vec};

    for (auto mul : muls) {
        auto const dim{1024u * mul};
        igs.emplace_back(dim, dim);
    }
    igs.back().create_directories();

    using Task = std::function<void()>;
    std::vector<Task> tasks;
    tasks.reserve(300);

    for (std::size_t i{0}; i < muls.size(); ++i) {
        auto& ig{igs[i]};
        tasks.emplace_back([&ig]() { ig.draw_circle(); });
        tasks.emplace_back([&ig]() { ig.draw_grid(); });
        tasks.emplace_back([&ig]() { ig.draw_rect_die(1, 1, prop); });
        tasks.emplace_back([&ig]() { ig.draw_x_die(0u, 2u, prop); });
        tasks.emplace_back([&ig]() { ig.draw_x_die(3u, 0u, prop); });
        tasks.emplace_back([&ig]() { ig.draw_rect_die(2, 2, prop); });
        tasks.emplace_back([&ig]() { ig.draw_x_die(3u, 3u, prop); });
        tasks.emplace_back([&ig]() { ig.draw_rect_die(3, 2, prop); });

        for (double x{0.1}; x < 0.9; x += 0.1) {
            tasks.emplace_back([&ig, x]() { ig.draw_square(x); });
        }
    }

    oneapi::tbb::parallel_for(std::size_t{0}, tasks.size(), [&](std::size_t i) { tasks[i](); });

    return 0;
}
