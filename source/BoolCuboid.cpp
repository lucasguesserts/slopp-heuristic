#include "BoolCuboid.hpp"

#include <utility>
#include <vector>

namespace packing {

BoolCuboid::BoolCuboid(const Size size)
    : _size{std::move(size)}
    , _data(size.x(), std::vector<std::vector<bool>>(size.y(), std::vector<bool>(size.z(), false))) {}


auto BoolCuboid::occupy(const Size & initial_position, const Size & final_position) -> void {
    for (auto x = initial_position.x(); x < final_position.x(); ++x) {
        for (auto y = initial_position.y(); y < final_position.y(); ++y) {
            for (auto z = initial_position.z(); z < final_position.z(); ++z) {
                this->_data[x][y][z] = true;
            }
        }
    }
    return;
}

} // namespace packing
