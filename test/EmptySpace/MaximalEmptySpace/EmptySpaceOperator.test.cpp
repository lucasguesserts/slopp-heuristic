#include "Test/Test.hpp"

#include "AllocatedSmallItem/Specialization/BasicAllocatedSmallItem.hpp"
#include "EmptySpace/MaximalEmptySpace/EmptySpaceOperator.hpp"
#include "EmptySpace/MaximalEmptySpace/Specialization/BasicEmptySpace.hpp"
#include "Geometry/Vector3D.hpp"
#include "SmallItem/Specialization/BasicSmallItem.hpp"

using namespace packing;
using namespace packing::maximal_empty_space;
using Catch::Matchers::UnorderedEquals;

TEST_CASE("cut_empty_space", "[EmptySpaceOperator]") {
    const auto empty_space_position = Vector3D{10, 20, 30};
    const auto empty_space_measurement = Vector3D{20, 30, 40};
    const auto empty_space = BasicEmptySpace{empty_space_position, empty_space_measurement};
    const auto empty_space_operator = EmptySpaceOperator<BasicSmallItem>{};
    SECTION("case 0 - the AllocatedItem and the EmptySpace have no overlap") {
        const auto position = Vector3D{100, 200, 300};
        const auto measurement = Vector3D{200, 300, 400};
        const auto quantity = Quantity{1};
        const auto small_item = std::make_shared<BasicSmallItem>(measurement, quantity);
        const auto allocated_item = BasicAllocatedSmallItem<BasicSmallItem>{small_item, position};
        const auto expected = std::vector<BasicEmptySpace>{empty_space};
        const auto actual = empty_space_operator.remaining_empty_space(empty_space, allocated_item);
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
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
        const auto actual = empty_space_operator.remaining_empty_space(empty_space, allocated_item);
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
        const auto actual = empty_space_operator.remaining_empty_space(empty_space, allocated_item);
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
        const auto actual = empty_space_operator.remaining_empty_space(empty_space, allocated_item);
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
        const auto actual = empty_space_operator.remaining_empty_space(empty_space, allocated_item);
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
        const auto actual = empty_space_operator.remaining_empty_space(empty_space, allocated_item);
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
    SECTION("case 10 - the AllocatedItem covers the whole EmptySpace") {
        const auto position = Vector3D{0, 0, 0};
        const auto measurement = Vector3D{100, 100, 100};
        const auto quantity = Quantity{1};
        const auto small_item = std::make_shared<BasicSmallItem>(measurement, quantity);
        const auto allocated_item = BasicAllocatedSmallItem<BasicSmallItem>{small_item, position};
        const auto expected = std::vector<BasicEmptySpace>{};
        const auto actual = empty_space_operator.remaining_empty_space(empty_space, allocated_item);
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
    // TODO: cases not tested:
    // "case 4 - the AllocatedItem gets into the EmptySpace from one plane without touching any corner point"
    // "case 6 - the AllocatedItem crosses one pair of parallel edges of the EmptySpace without touching any corner of the EmptySpace"
    // "case 7 - the AllocatedItem passes through one pair of parallel planes of the EmptySpace without any corner point of the EmptySpace"
    // "case 8 - the AllocatedItem cuts the EmptySpace into two new empty spaces"
}

TEST_CASE("add_to_collection", "[EmptySpaceOperator]") {
    const auto empty_space_collection = std::vector<BasicEmptySpace>{
        BasicEmptySpace{{2, 3, 4}, {3, 5, 7}},
        BasicEmptySpace{{4, 4, 5}, {4, 6, 8}},
        BasicEmptySpace{{1, 9, 9}, {5, 7, 9}},
        BasicEmptySpace{{9, 14, 19}, {10, 15, 20}},
    };
    const auto empty_space_operator = EmptySpaceOperator<BasicSmallItem>{};
    SECTION("e is not inside any Empty Space of S") {
        const auto empty_space = BasicEmptySpace({10, 1, 0}, {1, 2, 3});
        auto actual = empty_space_collection;
        empty_space_operator.add_to_collection(empty_space, actual);
        const auto expected = std::vector<BasicEmptySpace>{
            empty_space_collection[0],
            empty_space_collection[1],
            empty_space_collection[2],
            empty_space_collection[3],
            empty_space,
        };
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
    SECTION("e is inside one Empty Space of S") {
        const auto empty_space = BasicEmptySpace({3, 4, 5}, {1, 2, 3});
        auto actual = empty_space_collection;
        empty_space_operator.add_to_collection(empty_space, actual);
        const auto expected = empty_space_collection;
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
    SECTION("e is inside the union of two Empty Spaces e1, e2 in S, but it is not inside any of them") {
        const auto empty_space = BasicEmptySpace({3, 4, 6}, {3, 2, 2});
        auto actual = empty_space_collection;
        empty_space_operator.add_to_collection(empty_space, actual);
        const auto expected = std::vector<BasicEmptySpace>{
            empty_space_collection[0],
            empty_space_collection[1],
            empty_space_collection[2],
            empty_space_collection[3],
            empty_space,
        };
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
    SECTION("one Empty Space e' in S is inside e") {
        const auto empty_space = BasicEmptySpace({8, 13, 18}, {12, 17, 22});
        auto actual = empty_space_collection;
        empty_space_operator.add_to_collection(empty_space, actual);
        const auto expected = std::vector<BasicEmptySpace>{
            empty_space_collection[0],
            empty_space_collection[1],
            empty_space_collection[2],
            empty_space,
        };
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
    SECTION("three Empty Space e' in S are inside e, but one other e'' in S is not") {
        const auto empty_space = BasicEmptySpace({0, 0, 0}, {10, 17, 20});
        auto actual = empty_space_collection;
        empty_space_operator.add_to_collection(empty_space, actual);
        const auto expected = std::vector<BasicEmptySpace>{
            empty_space_collection[3],
            empty_space,
        };
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
    SECTION("all Empty Spaces e' in S are inside e") {
        const auto empty_space = BasicEmptySpace({1, 3, 4}, {18, 26, 35});
        auto actual = empty_space_collection;
        empty_space_operator.add_to_collection(empty_space, actual);
        const auto expected = std::vector<BasicEmptySpace>{
            empty_space,
        };
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
}

TEST_CASE("extend_collection", "[EmptySpaceOperator]") {
    const auto empty_space_collection = std::vector<BasicEmptySpace>{
        BasicEmptySpace{{2, 3, 4}, {3, 5, 7}},
        BasicEmptySpace{{4, 4, 5}, {4, 6, 8}},
        BasicEmptySpace{{1, 9, 9}, {5, 7, 9}},
        BasicEmptySpace{{9, 14, 19}, {10, 15, 20}},
    };
    const auto empty_space_operator = EmptySpaceOperator<BasicSmallItem>{};
    SECTION("equal collections") {
        auto actual = empty_space_collection;
        const auto extension = empty_space_collection;
        const auto expected = empty_space_collection;
        empty_space_operator.extend_collection(actual, extension);
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
    SECTION("disjoint collections") {
        auto actual = std::vector<BasicEmptySpace>{
            empty_space_collection[0],
            empty_space_collection[1],
        };
        const auto extension = std::vector<BasicEmptySpace>{
            empty_space_collection[2],
            empty_space_collection[3],
        };
        const auto expected = empty_space_collection;
        empty_space_operator.extend_collection(actual, extension);
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
    SECTION("two Empty Space of the extension are within collection and two are not") {
        auto actual = std::vector<BasicEmptySpace>{
            empty_space_collection[0],
            empty_space_collection[3],
        };
        const auto extension = std::vector<BasicEmptySpace>{
            // inside actual
            empty_space_collection[0],
            BasicEmptySpace{{9 + 1, 14 + 1, 19 + 1}, {10 - 2, 15 - 2, 20 - 2}},
            // outside actual
            empty_space_collection[1],
            empty_space_collection[2],
        };
        const auto expected = empty_space_collection;
        empty_space_operator.extend_collection(actual, extension);
        CHECK_THAT(actual, UnorderedEquals(expected));
    }
}
