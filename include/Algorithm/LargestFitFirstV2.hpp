#ifndef LARGEST_FIT_FIRST_ALGORITHM_V2_HPP_
#define LARGEST_FIT_FIRST_ALGORITHM_V2_HPP_

#include <vector>

#include "nlohmann/json.hpp"

#include "Algorithm/LargestFitFirst/BoolCuboid.hpp"
#include "Algorithm/LargestFitFirst/CornerPointIdentifier.hpp"
#include "Algorithm/LargestFitFirst/PriorityQueueOfVector3D.hpp"
#include "AllocatedSmallItem/Specialization/AllocatedSmallItemWithSurface.hpp"
#include "Geometry/Vector3D.hpp"
#include "Input/Specialization/BasicInput.hpp"
#include "LargeObject/Specialization/BasicLargeObject.hpp"
#include "LargestFitFirst.hpp"
#include "SmallItem/Container/QuantityManager.hpp"
#include "SmallItem/Specialization/SmallItemWithSurface.hpp"
#include "Timer/Timer.hpp"

namespace packing {
namespace algorithm {

    class LargestFitFirstV2 : public LargestFitFirst<SmallItemWithSurface, SmallItemWithSurface::Hash, AllocatedSmallItemWithSurface> {
    public:
        LargestFitFirstV2(BasicInput<SmallItemWithSurface> & data);

        auto allocate() -> void override;

    protected:
        PriorityQueueOfVector3D corner_points;
        CornerPointIdentifier corner_point_identifier;

        LargestFitFirstV2(const BasicLargeObject large_object);
    };

} // namespace algorithm

} // namespace packing

#endif
