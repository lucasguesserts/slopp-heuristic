#include <catch2/catch_test_macros.hpp>

#include <vector>

#include <cppitertools/itertools.hpp>

#include "AllocatedSmallItem.hpp"
#include "LargeObject.hpp"
#include "LargestFitFirstAlgorithm.hpp"
#include "SmallItem.hpp"
#include "SmallItemQuantityManager.hpp"
#include "Vector3D.hpp"

using namespace packing;

TEST_CASE("case 1", "[LargestFitFirstAlgorithm]") {
    // data
    const auto large_object = LargeObject{{5, 5, 5}};
    const auto small_items = std::vector<SmallItem>{
        {{5, 5, 5}},
    };
    const auto quantities = std::vector<Quantity>{
        1,
    };
    const auto expected_allocated_items = std::vector<AllocatedSmallItem>{
        {SmallItem{{5, 5, 5}}, Vector3D{0, 0, 0}},
    };
    // allocate
    auto algorithm = LargestFitFirstAlgorithm{large_object};
    for (auto && [small_item, quantity] : iter::zip(small_items, quantities)) {
        algorithm.add_item(small_item, quantity);
    }
    algorithm.allocate();
    const auto & small_items_allocated = algorithm.allocated_items();
    // check
    CHECK(small_items_allocated.size() == expected_allocated_items.size());
    for (const auto && [item, expected] : iter::zip(small_items_allocated, expected_allocated_items)) {
        CHECK(item == expected);
    }
}

TEST_CASE("case 2", "[LargestFitFirstAlgorithm]") {
    // data
    const auto large_object = LargeObject{{11, 11, 11}};
    const auto small_items = std::vector<SmallItem>{
        {{5, 5, 5}},
    };
    const auto quantities = std::vector<Quantity>{
        80,
    };
    const auto expected_allocated_items = std::vector<AllocatedSmallItem>{
        {SmallItem{{5, 5, 5}}, Vector3D{0, 0, 0}},
        {SmallItem{{5, 5, 5}}, Vector3D{5, 0, 0}},
        {SmallItem{{5, 5, 5}}, Vector3D{0, 5, 0}},
        {SmallItem{{5, 5, 5}}, Vector3D{5, 5, 0}},
        {SmallItem{{5, 5, 5}}, Vector3D{0, 0, 5}},
        {SmallItem{{5, 5, 5}}, Vector3D{5, 0, 5}},
        {SmallItem{{5, 5, 5}}, Vector3D{0, 5, 5}},
        {SmallItem{{5, 5, 5}}, Vector3D{5, 5, 5}},
    };
    // allocate
    auto algorithm = LargestFitFirstAlgorithm{large_object};
    for (auto && [small_item, quantity] : iter::zip(small_items, quantities)) {
        algorithm.add_item(small_item, quantity);
    }
    algorithm.allocate();
    const auto & small_items_allocated = algorithm.allocated_items();
    // check
    CHECK(small_items_allocated.size() == expected_allocated_items.size());
    for (const auto && [item, expected] : iter::zip(small_items_allocated, expected_allocated_items)) {
        CHECK(item == expected);
    }
}

TEST_CASE("case 3", "[LargestFitFirstAlgorithm]") {
    // data
    const auto large_object = LargeObject{{10, 10, 10}};
    const auto small_items = std::vector<SmallItem>{
        {{5, 5, 5}},
        {{1, 1, 1}},
    };
    const auto quantities = std::vector<Quantity>{
        1,
        1,
    };
    const auto expected_allocated_items = std::vector<AllocatedSmallItem>{
        {SmallItem{{5, 5, 5}}, Vector3D{0, 0, 0}},
        {SmallItem{{1, 1, 1}}, Vector3D{5, 0, 0}},
    };
    // allocate
    auto algorithm = LargestFitFirstAlgorithm{large_object};
    for (auto && [small_item, quantity] : iter::zip(small_items, quantities)) {
        algorithm.add_item(small_item, quantity);
    }
    algorithm.allocate();
    const auto & small_items_allocated = algorithm.allocated_items();
    // check
    CHECK(small_items_allocated.size() == expected_allocated_items.size());
    for (const auto && [item, expected] : iter::zip(small_items_allocated, expected_allocated_items)) {
        CHECK(item == expected);
    }
}

TEST_CASE("case 4", "[LargestFitFirstAlgorithm]") {
    // data
    const auto large_object = LargeObject{{10, 10, 10}};
    const auto small_items = std::vector<SmallItem>{
        {{6, 7, 10}},
        {{4, 10, 10}},
        {{10, 3, 10}},
    };
    const auto quantities = std::vector<Quantity>{
        1,
        1,
        1,
    };
    const auto expected_allocated_items = std::vector<AllocatedSmallItem>{
        {SmallItem{{6, 7, 10}}, Vector3D{0, 0, 0}},
        {SmallItem{{4, 10, 10}}, Vector3D{6, 0, 0}},
    };
    // allocate
    auto algorithm = LargestFitFirstAlgorithm{large_object};
    for (auto && [small_item, quantity] : iter::zip(small_items, quantities)) {
        algorithm.add_item(small_item, quantity);
    }
    algorithm.allocate();
    const auto & small_items_allocated = algorithm.allocated_items();
    // check
    CHECK(small_items_allocated.size() == expected_allocated_items.size());
    for (const auto && [item, expected] : iter::zip(small_items_allocated, expected_allocated_items)) {
        CHECK(item == expected);
    }
}
