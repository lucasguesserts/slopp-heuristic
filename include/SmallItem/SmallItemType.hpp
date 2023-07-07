#ifndef SMALL_ITEM_TYPE_HPP_
#define SMALL_ITEM_TYPE_HPP_

#include <cstddef>
#include <memory>

#include "Geometry/Vector3D.hpp"
#include "Type/Quantity.hpp"

namespace packing {

class SmallItemType {
public:
    SmallItemType() {}
    virtual ~SmallItemType() {}

    virtual auto measurement() const -> Vector3D = 0;
    virtual auto quantity() const -> Quantity = 0;

    virtual auto operator==(const SmallItemType & other) const -> bool;

    using Ptr = std::shared_ptr<SmallItemType>;

    struct Hash {
        auto operator()(const Ptr & small_item) const -> std::size_t;
    };
};

} // namespace packing

#endif
