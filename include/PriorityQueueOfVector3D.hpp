#ifndef VECTOR3D_QUEUE_HPP_
#define VECTOR3D_QUEUE_HPP_

#include <queue>
#include <vector>

#include "Vector3D.hpp"

namespace packing {

struct LessVector3D {
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

struct GreaterVector3D : LessVector3D {
public:
    auto operator()(const Vector3D & lhs, const Vector3D & rhs) const -> bool;
};

using PriorityQueueOfVector3D = std::priority_queue<Vector3D, std::vector<Vector3D>, GreaterVector3D>;

} // namespace packing

#endif
