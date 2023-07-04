#ifndef BASIC_LARGE_OBJECT_HPP_
#define BASIC_LARGE_OBJECT_HPP_

#include "LargeObject/LargeObjectType.hpp"
#include "Vector3D.hpp"

namespace packing {

class BasicLargeObject: public LargeObjectType {
public:
    BasicLargeObject(const Vector3D measurement);

    inline auto measurement() const -> Vector3D final override {
        return this->_measurement;
    }

private:
    Vector3D _measurement;
};

} // namespace packing

#endif
