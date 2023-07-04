#ifndef SMALL_ITEMS_QUANTITY_HPP_
#define SMALL_ITEMS_QUANTITY_HPP_

#include <cstddef>
#include <unordered_map>

#include <boost/functional/hash.hpp>

#include "SmallItem.hpp"

namespace packing {

using Quantity = unsigned;

struct SmallItemHash {
    auto operator()(const SmallItem & small_item) const -> std::size_t;
};

class SmallItemQuantityManager : public std::unordered_map<SmallItem, Quantity, SmallItemHash> {};

} // namespace packing

#endif
