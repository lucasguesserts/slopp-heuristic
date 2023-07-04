#include "Test/Test.hpp"

#include <algorithm>
#include <itertools.hpp>
#include <vector>

#include "Algorithm/LargestFitFirst/OrderedSmallItems.hpp"
#include "SmallItem.hpp"
#include "Geometry/Vector3D.hpp"

using namespace packing;

auto sort_items_descendig_volume(std::vector<SmallItem> small_items) -> decltype(small_items) {
    std::sort(
        small_items.begin(),
        small_items.end(),
        [](const SmallItem & lhs, const SmallItem & rhs) {
            return lhs.size().volume() < rhs.size().volume();
        });
    std::reverse(small_items.begin(), small_items.end());
    return small_items;
}

TEST_CASE("order", "[SmallItem]") {
    const auto small_items = std::vector<SmallItem>{
        {{1, 1, 1}},
        {{1, 1, 1}},
        {{1, 1, 2}},
        {{1, 1, 2}},
        {{1, 2, 2}},
        {{3, 4, 5}},
        {{6, 7, 8}},
        {{6, 7, 8}},
    };
    const auto sorted_small_items = sort_items_descendig_volume(small_items);
    const OrderedSmallItems ordered_small_items{small_items.cbegin(), small_items.cend()};
    for (const auto && [ordered, sorted] : iter::zip(ordered_small_items, sorted_small_items)) {
        CHECK(ordered == sorted);
    }
}
