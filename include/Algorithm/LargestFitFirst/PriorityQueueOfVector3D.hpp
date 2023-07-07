#ifndef VECTOR3D_QUEUE_HPP_
#define VECTOR3D_QUEUE_HPP_

#include <queue>
#include <vector>

#include "Geometry/Vector3D.hpp"

namespace packing {

struct GreaterVector3D {
public:
    auto operator()(const Vector3D & lhs, const Vector3D & rhs) const -> bool;

private:
    enum class Comparison {
        SMALLER = -1,
        EQUALS = 0,
        GREATER = 1
    };
    auto compare(const CoordinateType & lhs, const CoordinateType & rhs) const -> Comparison;
};

using PriorityQueueOfVector3D = std::priority_queue<Vector3D, std::vector<Vector3D>, GreaterVector3D>;
// using Greater make the smallest appear at the top

} // namespace packing

#endif
