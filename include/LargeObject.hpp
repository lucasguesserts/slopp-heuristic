#ifndef LARGE_OBJECT_HPP_
#define LARGE_OBJECT_HPP_

#include "Size.hpp"

namespace packing {

class LargeObject {
public:
    LargeObject(const Size size);
    [[nodiscard]] auto size() const -> Size {
        return this->_size;
    }

private:
    Size _size;
};

} // namespace packing

#endif
