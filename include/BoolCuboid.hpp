#ifndef BOOL_MATRIX_HPP_
#define BOOL_MATRIX_HPP_

#include <cstddef>
#include <utility>
#include <vector>

#include "Geometry/Vector3D.hpp"

namespace packing {

class BoolCuboid {
public:
    BoolCuboid(const Vector3D size);

    [[nodiscard]] auto size() const -> Vector3D {
        return this->_size;
    }

    [[nodiscard]] static auto all_entries(const Vector3D & initial_position, const Vector3D & final_position);

    [[nodiscard]] auto is_outside(const Vector3D & position) const -> bool;

    [[nodiscard]] auto is_occupied(const CoordinateType & x, const CoordinateType & y, const CoordinateType & z) const -> bool {
        return this->_data[x][y][z];
    }
    [[nodiscard]] auto is_free(const CoordinateType & x, const CoordinateType & y, const CoordinateType & z) const -> bool {
        return !this->is_occupied(x, y, z);
    }

    [[nodiscard]] auto is_any_occupied(const Vector3D & initial_position, const Vector3D & final_position) const -> bool;
    [[nodiscard]] auto are_all_free(const Vector3D & initial_position, const Vector3D & final_position) const -> bool;

    auto occupy(const Vector3D & initial_position, const Vector3D & final_position) -> void;

private:
    const Vector3D _size;
    std::vector<std::vector<std::vector<bool>>> _data;
};

} // namespace packing

#endif
