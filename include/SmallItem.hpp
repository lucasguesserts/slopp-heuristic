#ifndef SMALL_ITEM_HPP
#define SMALL_ITEM_HPP

#include "Size.hpp"

namespace packing {

class SmallItem {
public:
    SmallItem(const Size size);
    [[nodiscard]] auto size() const -> Size {
        return this->_size;
    }

    auto operator==(const SmallItem & other) const -> bool;

private:
    Size _size;
};

} // namespace packing

#endif
