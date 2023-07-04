#include "AllocatedSmallItem/Specialization/AllocatedSmallItemWithSurface.hpp"

#include <algorithm>
#include <iterator>
#include <utility>

#include "Geometry/Surface.hpp"

namespace packing {

AllocatedSmallItemWithSurface::AllocatedSmallItemWithSurface(const std::shared_ptr<SmallItemWithSurface> type, const Vector3D position)
    : BasicAllocatedSmallItem<SmallItemWithSurface>{std::move(type), std::move(position)} {}

auto AllocatedSmallItemWithSurface::surface() const -> Surface {
    const auto small_item_surface = this->type().surface();
    auto points = Surface{};
    std::transform(
        small_item_surface.cbegin(),
        small_item_surface.cend(),
        std::inserter(points, points.end()),
        [this](const auto & point) {
            return point + this->position();
        });
    return points;
}

}
