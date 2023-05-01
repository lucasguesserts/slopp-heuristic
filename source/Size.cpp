#include "Size.hpp"
#include <utility>

namespace packing {

Size::Size(const SizeType x, const SizeType y, const SizeType z)
    : _x(std::move(x))
    , _y(std::move(y))
    , _z(std::move(z)) {}

} // namespace packing
