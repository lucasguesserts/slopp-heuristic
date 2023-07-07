#ifndef BASIC_SMALL_ITEM_HPP_
#define BASIC_SMALL_ITEM_HPP_

#include <memory>

#include "Geometry/Vector3D.hpp"
#include "SmallItem/SmallItemType.hpp"

namespace packing {

class BasicSmallItem : public SmallItemType {
public:
    BasicSmallItem(const Vector3D measurement, const Quantity quantity);
    ~BasicSmallItem() {}

    inline auto measurement() const -> Vector3D final override {
        return this->_measurement;
    }
    inline auto quantity() const -> Quantity final override {
        return this->_quantity;
    }

    using Ptr = std::shared_ptr<BasicSmallItem>;

private:
    Vector3D _measurement;
    Quantity _quantity;
};

} // namespace packing

#endif
