#include <cstddef>
#include <cstdint>

namespace sbx {
class Dimension {
  public:
    using value_type = std::uint64_t;

    Dimension() = default;
    Dimension(value_type dim)
        : dim_{dim} {}

    operator double() const { return static_cast<double>(dim_); }
    double as_double() const { return *this; }
  private:
    value_type dim_{00};
};

}
