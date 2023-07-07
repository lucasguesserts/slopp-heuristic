#include "Algorithm/LargestFitFirst/PriorityQueueOfVector3D.hpp"
#include "Geometry/Vector3D.hpp"

namespace packing {

auto GreaterVector3D::operator()(const Vector3D & lhs, const Vector3D & rhs) const -> bool {
    // this is actually a greate comparator
    const auto z_comparison = compare(lhs.z(), rhs.z());
    if (z_comparison == Comparison::SMALLER) {
        return false;
    } else if (z_comparison == Comparison::GREATER) {
        return true;
    }
    const auto x_comparison = compare(lhs.x(), rhs.x());
    if (x_comparison == Comparison::SMALLER) {
        return false;
    } else if (x_comparison == Comparison::GREATER) {
        return true;
    }
    const auto y_comparison = compare(lhs.y(), rhs.y());
    if (y_comparison == Comparison::SMALLER) {
        return false;
    } else if (y_comparison == Comparison::GREATER) {
        return true;
    }
    return false; // equals case
}

auto GreaterVector3D::compare(const CoordinateType & lhs, const CoordinateType & rhs) const -> Comparison {
    if (lhs < rhs) return Comparison::SMALLER;
    else if (lhs > rhs) return Comparison::GREATER;
    else return Comparison::EQUALS;
}

} // namespace packing
