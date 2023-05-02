#include "SmallItemQuantityManager.hpp"

namespace packing {

auto SmallItemHash::operator()(const SmallItem & small_item) const -> std::size_t {
    std::size_t seed = 0;
    boost::hash_combine(seed, small_item.size().x());
    boost::hash_combine(seed, small_item.size().y());
    boost::hash_combine(seed, small_item.size().z());
    return seed;
}

} // namespace packing
