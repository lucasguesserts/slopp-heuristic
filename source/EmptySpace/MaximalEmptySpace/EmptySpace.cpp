#include "EmptySpace/MaximalEmptySpace/EmptySpace.hpp"

namespace packing {

namespace maximal_empty_space {

    auto EmptySpace::is_inside(const EmptySpace & other) const -> bool {
        return this->position().x() >= other.position().x() && this->position().y() >= other.position().y() && this->position().z() >= other.position().z() && this->final_position().x() <= other.final_position().x() && this->final_position().y() <= other.final_position().y() && this->final_position().z() <= other.final_position().z();
    }

    auto EmptySpace::operator==(const EmptySpace & rhs) const -> bool {
        return this->position() == rhs.position() && this->measurement() == rhs.measurement();
    }

} // namespace maximal_empty_space

} // namespace packing
