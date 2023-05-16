#ifndef ALLOCATED_SMALL_ITEM_HPP
#define ALLOCATED_SMALL_ITEM_HPP

#include "SmallItem.hpp"
#include "Surface.hpp"
#include "Vector3D.hpp"

namespace packing {

class AllocatedSmallItem : public SmallItem {
public:
    AllocatedSmallItem(const SmallItem & small_item, const Vector3D position);

    [[nodiscard]] auto position() const -> Vector3D {
        return this->_position;
    }

    auto surface() const -> Surface;

    auto operator==(const AllocatedSmallItem & other) const -> bool;

private:
    Vector3D _position;
};

} // namespace packing

#endif
