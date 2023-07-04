#include "SmallItem/SmallItemType.hpp"

#include "Vector3D.hpp"

namespace packing {

auto SmallItemType::operator==(const SmallItemType &other) const -> bool {
    return (this->measurement() == other.measurement()) && (this->quantity() == other.quantity());
}

} // namespace packing
