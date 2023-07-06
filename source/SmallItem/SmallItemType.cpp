#include "SmallItem/SmallItemType.hpp"

#include <boost/functional/hash.hpp>

#include "Geometry/Vector3D.hpp"

namespace packing {

auto SmallItemType::operator==(const SmallItemType & other) const -> bool {
    return (this->measurement() == other.measurement()) && (this->quantity() == other.quantity());
}

auto SmallItemType::Hash::operator()(const Ptr & small_item) const -> std::size_t {
    std::size_t seed = 0;
    boost::hash_combine(seed, small_item->measurement().x());
    boost::hash_combine(seed, small_item->measurement().y());
    boost::hash_combine(seed, small_item->measurement().z());
    boost::hash_combine(seed, small_item->quantity());
    return seed;
}

} // namespace packing
