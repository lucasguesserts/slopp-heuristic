#include "LargeObject/LargeObjectType.hpp"

namespace packing {

auto LargeObjectType::operator==(const LargeObjectType & other) const -> bool {
    return this->measurement() == other.measurement();
}

} // namespace packing
