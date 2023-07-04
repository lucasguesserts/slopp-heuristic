#ifndef ALLOCATED_SMALL_ITEM_WITH_SURFACE_HPP_
#define ALLOCATED_SMALL_ITEM_WITH_SURFACE_HPP_

#include "AllocatedSmallItem/BasicAllocatedSmallItem.hpp"
#include "SmallItem/Specialization/SmallItemWithSurface.hpp"

namespace packing {

class AllocatedSmallItemWithSurface : public BasicAllocatedSmallItem<SmallItemWithSurface> {
public:
    AllocatedSmallItemWithSurface(const std::shared_ptr<SmallItemWithSurface> type, const Vector3D position);

    virtual auto surface() const -> Surface;
};

} // namespace packing

#endif
