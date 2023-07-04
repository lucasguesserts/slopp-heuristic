#ifndef LARGE_OBJECT_TYPE_HPP_
#define LARGE_OBJECT_TYPE_HPP_

#include "Vector3D.hpp"

namespace packing {

class LargeObjectType {
public:
    LargeObjectType(){};
    virtual ~LargeObjectType(){};

    virtual auto measurement() const -> Vector3D = 0;
};

} // namespace packing

#endif
