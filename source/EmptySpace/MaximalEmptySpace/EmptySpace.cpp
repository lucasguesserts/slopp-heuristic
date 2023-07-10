#include "EmptySpace/MaximalEmptySpace/EmptySpace.hpp"

namespace packing {

namespace maximal_empty_space {

auto EmptySpace::operator==(const EmptySpace & rhs) const -> bool {
    return this->position() == rhs.position() && this->measurement() == rhs.measurement();
}

} // namespace maximal_empty_space

} // namespace packing
