#ifndef ALLOCATED_SMALL_ITEM_HPP_
#define ALLOCATED_SMALL_ITEM_HPP_

#include <memory>
#include <utility>

#include "Geometry/Vector3D.hpp"

namespace packing {

template <typename ItemType>
class AllocatedSmallItem {
public:
    virtual auto type() const -> ItemType = 0;
    virtual auto position() const -> Vector3D = 0;
    virtual auto final_position() const -> Vector3D = 0;

    virtual auto operator==(const AllocatedSmallItem & other) const -> bool {
        return this->type() == other.type() && this->position() == other.position();
    }
};

} // namespace packing

#endif
