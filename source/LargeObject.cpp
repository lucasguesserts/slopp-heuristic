#include "LargeObject.hpp"

#include <utility>

#include "Size.hpp"

namespace packing {

LargeObject::LargeObject(const Size size)
    : _size(std::move(size)) {}

} // namespace packing
