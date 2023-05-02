#ifndef BOOL_MATRIX_HPP_
#define BOOL_MATRIX_HPP_

#include <cstddef>
#include <utility>
#include <vector>

#include "Vector3D.hpp"

namespace packing {

class BoolCuboid {
public:
    BoolCuboid(const Vector3D size);

    [[nodiscard]] auto size() const -> Vector3D {
        return this->_size;
    }

    auto operator()(const CoordinateType & x, const CoordinateType & y, const CoordinateType & z) const -> bool {
        return this->_data[x][y][z];
    }

    auto occupy(const Vector3D & initial_position, const Vector3D & final_position) -> void;

private:
    const Vector3D _size;
    std::vector<std::vector<std::vector<bool>>> _data;
};

} // namespace packing

#endif
