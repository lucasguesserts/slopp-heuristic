#include "SmallItem/BasicSmallItem.hpp"

#include <utility>

#include "Geometry/Vector3D.hpp"
#include "SmallItem/SmallItemType.hpp"

namespace packing {

BasicSmallItem::BasicSmallItem(const Vector3D measurement, const Quantity quantity)
    : SmallItemType()
    , _measurement(std::move(measurement))
    , _quantity(quantity) {}

} // namespace packing
