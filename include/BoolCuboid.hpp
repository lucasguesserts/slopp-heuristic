#ifndef BOOL_MATRIX_HPP_
#define BOOL_MATRIX_HPP_

#include <cstddef>
#include <utility>
#include <vector>

#include "Size.hpp"

namespace packing {

class BoolCuboid {
public:
    BoolCuboid(const Size size);

    [[nodiscard]] auto size() const -> Size {
        return this->_size;
    }

    auto operator()(const SizeType & x, const SizeType & y, const SizeType & z) const -> bool {
        return this->_data[x][y][z];
    }

private:
    const Size _size;
    std::vector<std::vector<std::vector<bool>>> _data;
};

} // namespace packing

#endif
