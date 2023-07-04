#ifndef SMALL_ITEM_TYPE_HPP_
#define SMALL_ITEM_TYPE_HPP_

#include "Vector3D.hpp"

namespace packing {

using Quantity = unsigned;

class SmallItemType {
public:
    SmallItemType() {}
    virtual ~SmallItemType() {}

    virtual auto measurement() const -> Vector3D = 0;
    virtual auto quantity() const -> Quantity = 0;

    virtual auto operator==(const SmallItemType & other) const -> bool;
};

} // namespace packing

#endif
