#include "BoolCuboid.hpp"

#include <utility>
#include <vector>

namespace packing {

BoolCuboid::BoolCuboid(const Size size)
    : _size{std::move(size)}
    , _data(size.x(), std::vector<std::vector<bool>>(size.y(), std::vector<bool>(size.z(), false))) {}

} // namespace packing
