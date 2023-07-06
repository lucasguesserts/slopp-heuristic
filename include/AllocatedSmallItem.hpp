#ifndef ALLOCATED_SMALL_ITEM_HPP
#define ALLOCATED_SMALL_ITEM_HPP

#include "Geometry/Surface.hpp"
#include "Geometry/Vector3D.hpp"
#include "SmallItem.hpp"

namespace packing {

class AllocatedSmallItem : public SmallItem {
public:
    AllocatedSmallItem(const SmallItem & small_item, const Vector3D position);

    [[nodiscard]] auto position() const -> Vector3D {
        return this->_position;
    }

    auto surface() const -> Surface override;

    auto operator==(const AllocatedSmallItem & other) const -> bool;

private:
    Vector3D _position;
};

} // namespace packing

#endif
