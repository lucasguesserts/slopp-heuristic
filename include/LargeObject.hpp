#ifndef LARGE_OBJECT_HPP_
#define LARGE_OBJECT_HPP_

#include "Vector3D.hpp"

namespace packing {

class LargeObject {
public:
    LargeObject(const Vector3D size);
    [[nodiscard]] auto size() const -> Vector3D {
        return this->_size;
    }

private:
    Vector3D _size;
};

} // namespace packing

#endif
