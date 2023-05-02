#include "BoolCuboid.hpp"

#include <utility>
#include <vector>

#include <cppitertools/itertools.hpp>

namespace packing {

BoolCuboid::BoolCuboid(const Vector3D size)
    : _size{std::move(size)}
    , _data(size.x(), std::vector<std::vector<bool>>(size.y(), std::vector<bool>(size.z(), false))) {}


auto BoolCuboid::occupy(const Vector3D & initial_position, const Vector3D & final_position) -> void {
    const auto range_x = iter::range(initial_position.x(), final_position.x());
    const auto range_y = iter::range(initial_position.y(), final_position.y());
    const auto range_z = iter::range(initial_position.z(), final_position.z());
    for (auto&& [x, y, z] : iter::product(range_x, range_y, range_z)) {
        this->_data[x][y][z] = true;
    }
    return;
}

} // namespace packing
