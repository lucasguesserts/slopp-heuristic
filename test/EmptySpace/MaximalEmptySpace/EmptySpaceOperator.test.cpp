#include "Test/Test.hpp"

#include "AllocatedSmallItem/Specialization/BasicAllocatedSmallItem.hpp"
#include "EmptySpace/MaximalEmptySpace/EmptySpaceOperator.hpp"
#include "EmptySpace/MaximalEmptySpace/Specialization/BasicEmptySpace.hpp"
#include "Geometry/Vector3D.hpp"
#include "SmallItem/Specialization/BasicSmallItem.hpp"

using namespace packing;
using namespace packing::maximal_empty_space;
using Catch::Matchers::UnorderedEquals;

TEST_CASE("EmptySpaceOperator", "[EmptySpaceOperator]") {
    const auto position = Vector3D{10, 20, 30};
    const auto measurement = Vector3D{20, 30, 40};
    const auto empty_space = BasicEmptySpace{position, measurement};
    const auto empty_space_operator = EmptySpaceOperator<BasicSmallItem>{};
    SECTION("case 1 - the AllocatedItem intersects one corner of the EmptySpace") {
        const auto position = Vector3D{9, 19, 29};
        const auto measurement = Vector3D{5, 7, 11};
        const auto quantity = Quantity{1};
        const auto small_item = std::make_shared<BasicSmallItem>(measurement, quantity);
        const auto allocated_item = BasicAllocatedSmallItem<BasicSmallItem>{small_item, position};
        const auto expected = std::vector<BasicEmptySpace>{
            BasicEmptySpace{{14, 20, 30}, {16, 30, 40}},
            BasicEmptySpace{{10, 26, 30}, {20, 24, 40}},
            BasicEmptySpace{{10, 20, 40}, {20, 30, 30}},
        };
        const auto actual = empty_space_operator.cut_empty_space(empty_space, allocated_item);
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
    SECTION("case 2 - the AllocatedItem intersects one entire edge of the EmptySpace") {
        const auto position = Vector3D{10, 20, 65};
        const auto measurement = Vector3D{10, 30, 5};
        const auto quantity = Quantity{1};
        const auto small_item = std::make_shared<BasicSmallItem>(measurement, quantity);
        const auto allocated_item = BasicAllocatedSmallItem<BasicSmallItem>{small_item, position};
        const auto expected = std::vector<BasicEmptySpace>{
            BasicEmptySpace{{20, 20, 30}, {10, 30, 40}},
            BasicEmptySpace{{10, 20, 30}, {20, 30, 35}},
        };
        const auto actual = empty_space_operator.cut_empty_space(empty_space, allocated_item);
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
    SECTION("case 3 - the AllocatedItem intersects part of one edge of the EmptySpace") {
        const auto position = Vector3D{20, 29, 30};
        const auto measurement = Vector3D{25, 10, 5};
        const auto quantity = Quantity{1};
        const auto small_item = std::make_shared<BasicSmallItem>(measurement, quantity);
        const auto allocated_item = BasicAllocatedSmallItem<BasicSmallItem>{small_item, position};
        const auto expected = std::vector<BasicEmptySpace>{
            BasicEmptySpace{{10, 20, 30}, {20, 9, 40}},
            BasicEmptySpace{{10, 39, 30}, {20, 11, 40}},
            BasicEmptySpace{{10, 20, 30}, {10, 30, 40}},
            BasicEmptySpace{{10, 20, 35}, {20, 30, 35}},
        };
        const auto actual = empty_space_operator.cut_empty_space(empty_space, allocated_item);
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
    SECTION("case 5 - the AllocatedItem cuts away an entire plane of the EmptySpace") {
        const auto position = Vector3D{10, 20, 30};
        const auto measurement = Vector3D{5, 30, 40};
        const auto quantity = Quantity{1};
        const auto small_item = std::make_shared<BasicSmallItem>(measurement, quantity);
        const auto allocated_item = BasicAllocatedSmallItem<BasicSmallItem>{small_item, position};
        const auto expected = std::vector<BasicEmptySpace>{
            BasicEmptySpace{{15, 20, 30}, {15, 30, 40}},
        };
        const auto actual = empty_space_operator.cut_empty_space(empty_space, allocated_item);
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
    SECTION("case 9 - the whole AllocatedItem resides in the EmptySpace") {
        const auto position = Vector3D{20, 35, 50};
        const auto measurement = Vector3D{5, 7, 10};
        const auto quantity = Quantity{1};
        const auto small_item = std::make_shared<BasicSmallItem>(measurement, quantity);
        const auto allocated_item = BasicAllocatedSmallItem<BasicSmallItem>{small_item, position};
        const auto expected = std::vector<BasicEmptySpace>{
            BasicEmptySpace{{10, 20, 30}, {10, 30, 40}},
            BasicEmptySpace{{25, 20, 30}, {5, 30, 40}},
            BasicEmptySpace{{10, 20, 30}, {20, 15, 40}},
            BasicEmptySpace{{10, 20, 30}, {20, 30, 20}},
            BasicEmptySpace{{10, 42, 30}, {20, 8, 40}},
            BasicEmptySpace{{10, 20, 60}, {20, 30, 10}},
        };
        const auto actual = empty_space_operator.cut_empty_space(empty_space, allocated_item);
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
    SECTION("case 10 - the AllocatedItem covers the whole EmptySpace") {
        const auto position = Vector3D{0, 0, 0};
        const auto measurement = Vector3D{100, 100, 100};
        const auto quantity = Quantity{1};
        const auto small_item = std::make_shared<BasicSmallItem>(measurement, quantity);
        const auto allocated_item = BasicAllocatedSmallItem<BasicSmallItem>{small_item, position};
        const auto expected = std::vector<BasicEmptySpace>{};
        const auto actual = empty_space_operator.cut_empty_space(empty_space, allocated_item);
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
}

// "case 3 - the AllocatedItem intersects part of one edge of the EmptySpace"
// "case 4 - the AllocatedItem gets into the EmptySpace from one plane without touching any corner point"
// "case 6 - the AllocatedItem crosses one pair of parallel edges of the EmptySpace without touching any corner of the EmptySpace"
// "case 7 - the AllocatedItem passes through one pair of parallel planes of the EmptySpace without any corner point of the EmptySpace"
// "case 8 - the AllocatedItem cuts the EmptySpace into two new empty spaces"
