#ifndef LARGEST_FIT_FIRST_ALGORITHM_V3_HPP_
#define LARGEST_FIT_FIRST_ALGORITHM_V3_HPP_

#include <vector>

#include "SmallItem/Specialization/BasicSmallItem.hpp"
#include "nlohmann/json.hpp"

#include "AllocatedSmallItem/Specialization/BasicAllocatedSmallItem.hpp"
#include "EmptySpace/MaximalEmptySpace/EmptySpaceOperator.hpp"
#include "EmptySpace/MaximalEmptySpace/Specialization/BasicEmptySpace.hpp"
#include "Geometry/Vector3D.hpp"
#include "Input/Specialization/BasicInput.hpp"
#include "LargeObject/Specialization/BasicLargeObject.hpp"
#include "LargestFitFirst.hpp"
#include "SmallItem/Container/OrderedSmallItemsByVolume.hpp"
#include "SmallItem/Container/QuantityManager.hpp"
#include "Timer/Timer.hpp"

namespace packing {
namespace algorithm {

    class LargestFitFirstV3 : public LargestFitFirst<BasicSmallItem, BasicSmallItem::Hash, BasicAllocatedSmallItem<BasicSmallItem>> {
    public:
        LargestFitFirstV3(BasicInput<BasicSmallItem> & data);

        auto allocate() -> void override;

    protected:
        std::vector<maximal_empty_space::BasicEmptySpace> empty_spaces;
        maximal_empty_space::EmptySpaceOperator<BasicSmallItem> empty_space_operator;

        LargestFitFirstV3(const BasicLargeObject large_object);

        auto item_fit_in_space(
            const BasicSmallItem & small_item,
            const maximal_empty_space::BasicEmptySpace & empty_space) const -> bool;

        auto place_item(
            const BasicSmallItem::Ptr small_item,
            const maximal_empty_space::BasicEmptySpace & empty_space) -> void;
    };

} // namespace algorithm

} // namespace packing

#endif
