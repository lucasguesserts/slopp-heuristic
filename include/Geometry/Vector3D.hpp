#ifndef VECTOR3D_HPP_
#define VECTOR3D_HPP_

namespace packing {

using CoordinateType = long int;

class Vector3D {
public:
    Vector3D(const CoordinateType x, const CoordinateType y, const CoordinateType z);

    [[nodiscard]] auto x() const -> CoordinateType {
        return this->_x;
    }

    [[nodiscard]] auto y() const -> CoordinateType {
        return this->_y;
    }

    [[nodiscard]] auto z() const -> CoordinateType {
        return this->_z;
    }

    [[nodiscard]] auto volume() const -> CoordinateType {
        return this->x() * this->y() * this->z();
    }

    auto operator==(const Vector3D & other) const -> bool;
    auto operator+(const Vector3D & other) const -> Vector3D;

private:
    CoordinateType _x;
    CoordinateType _y;
    CoordinateType _z;
};

auto operator<(const Vector3D & lhs, const Vector3D & rhs) -> bool;
auto operator<=(const Vector3D & lhs, const Vector3D & rhs) -> bool;

} // namespace packing

#endif
