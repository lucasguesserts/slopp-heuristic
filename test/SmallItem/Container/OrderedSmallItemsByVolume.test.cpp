#include "Test/Test.hpp"

#include <algorithm>
#include <itertools.hpp>
#include <vector>

#include "Geometry/Vector3D.hpp"
#include "SmallItem/BasicSmallItem.hpp"
#include "SmallItem/Container/OrderedSmallItemsByVolume.hpp"

using namespace packing;

auto sort_items_descendig_volume(std::vector<BasicSmallItem::Ptr> small_items) -> decltype(small_items) {
    std::sort(
        small_items.begin(),
        small_items.end(),
        [](const BasicSmallItem::Ptr & lhs, const BasicSmallItem::Ptr & rhs) {
            return lhs->measurement().volume() < rhs->measurement().volume();
        });
    std::reverse(small_items.begin(), small_items.end());
    return small_items;
}

TEST_CASE("order", "[OrderedSmallItemsByVolume]") {
    const auto small_items = std::vector<BasicSmallItem::Ptr>{
        std::make_shared<BasicSmallItem>(Vector3D{1, 1, 1}, 1),
        std::make_shared<BasicSmallItem>(Vector3D{1, 1, 1}, 1),
        std::make_shared<BasicSmallItem>(Vector3D{1, 1, 2}, 1),
        std::make_shared<BasicSmallItem>(Vector3D{1, 1, 2}, 1),
        std::make_shared<BasicSmallItem>(Vector3D{1, 2, 2}, 1),
        std::make_shared<BasicSmallItem>(Vector3D{3, 4, 5}, 1),
        std::make_shared<BasicSmallItem>(Vector3D{6, 7, 8}, 1),
        std::make_shared<BasicSmallItem>(Vector3D{6, 7, 8}, 1),
    };
    const auto sorted_small_items = sort_items_descendig_volume(small_items);
    const OrderedSmallItemsByVolume<BasicSmallItem::Ptr> ordered_small_items{small_items.cbegin(), small_items.cend()};
    for (const auto && [ordered, sorted] : iter::zip(ordered_small_items, sorted_small_items)) {
        CHECK(*ordered == *sorted);
    }
}
