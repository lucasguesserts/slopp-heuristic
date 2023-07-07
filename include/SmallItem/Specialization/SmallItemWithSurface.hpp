#ifndef SMALL_ITEM_WITH_SURFACE_HPP_
#define SMALL_ITEM_WITH_SURFACE_HPP_

#include "Geometry/Surface.hpp"
#include "Geometry/Vector3D.hpp"
#include "SmallItem/BasicSmallItem.hpp"

namespace packing {

class SmallItemWithSurface : public BasicSmallItem {
public:

    using Ptr = std::shared_ptr<SmallItemWithSurface>;

    SmallItemWithSurface(const Vector3D measurement, const Quantity quantity);

    virtual auto surface() const -> Surface;
};

} // namespace packing

#endif
