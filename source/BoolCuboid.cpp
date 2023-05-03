#include "BoolCuboid.hpp"

#include <utility>
#include <vector>

#include <itertools.hpp>

namespace packing {

auto BoolCuboid::all_entries(
    const Vector3D & initial_position,
    const Vector3D & final_position) {
    return iter::product(
        iter::range(initial_position.x(), final_position.x()),
        iter::range(initial_position.y(), final_position.y()),
        iter::range(initial_position.z(), final_position.z()));
}

BoolCuboid::BoolCuboid(const Vector3D size)
    : _size{std::move(size)}
    , _data(size.x(), std::vector<std::vector<bool>>(size.y(), std::vector<bool>(size.z(), false))) {}

auto BoolCuboid::occupy(const Vector3D & initial_position, const Vector3D & final_position) -> void {
    auto all_entries = BoolCuboid::all_entries(initial_position, final_position);
    for (const auto && [x, y, z] : all_entries) {
        this->_data[x][y][z] = true;
    }
    return;
}

auto BoolCuboid::is_any_occupied(
    const Vector3D & initial_position,
    const Vector3D & final_position) const
    -> bool {
    for (const auto && [x, y, z] : BoolCuboid::all_entries(initial_position, final_position)) {
        if (this->is_occupied(x, y, z)) {
            return true;
        }
    }
    return false;
}

auto BoolCuboid::are_all_free(
    const Vector3D & initial_position,
    const Vector3D & final_position) const
    -> bool {
    return !this->is_any_occupied(initial_position, final_position);
}

} // namespace packing
