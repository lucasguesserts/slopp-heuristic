#ifndef SMALL_ITEM_HPP
#define SMALL_ITEM_HPP

#include "Surface.hpp"
#include "Vector3D.hpp"

namespace packing {

class SmallItem {
public:
    SmallItem(const Vector3D size);
    [[nodiscard]] auto size() const -> Vector3D {
        return this->_size;
    }

    auto surface() const -> Surface;

    auto operator==(const SmallItem & other) const -> bool;

private:
    Vector3D _size;
};

} // namespace packing

#endif
