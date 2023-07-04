#include "Test/Test.hpp"

#include "Algorithm/LargestFitFirst/PriorityQueueOfVector3D.hpp"
#include "Geometry/Vector3D.hpp"

#include <vector>

using namespace packing;

TEST_CASE("greater", "[PriorityQueueOfVector3D]") {
    const auto greater = GreaterVector3D();
    SECTION("false") {
        CHECK_FALSE(greater({1, 2, 3}, {1, 2, 3}));
        CHECK_FALSE(greater({9, 9, 0}, {1, 2, 3}));
        CHECK_FALSE(greater({0, 9, 3}, {1, 2, 3}));
        CHECK_FALSE(greater({1, 0, 3}, {1, 2, 3}));

        CHECK_FALSE(greater({0, 2, 3}, {1, 0, 3}));
        CHECK_FALSE(greater({1, 2, 0}, {0, 0, 1}));
    }
    SECTION("true") {
        CHECK(greater({1, 2, 3}, {9, 9, 0}));
        CHECK(greater({1, 2, 3}, {0, 9, 3}));
        CHECK(greater({1, 2, 3}, {1, 0, 3}));

        CHECK(greater({1, 0, 3}, {0, 2, 3}));
        CHECK(greater({0, 0, 1}, {1, 2, 0}));

        CHECK(greater({1, 2, 9}, {9, 9, 3}));
        CHECK(greater({9, 2, 3}, {1, 9, 3}));
        CHECK(greater({1, 9, 3}, {1, 2, 3}));
    }
}

TEST_CASE("constructor", "[PriorityQueueOfVector3D]") {
    const auto x = std::vector<Vector3D>{
        {1, 2, 3},
        {2, 3, 4},
        {1, 2, 0},
        {1, 0, 3},
        {0, 2, 3},
    };
    const auto sort_order = std::vector<unsigned>{2, 4, 3, 0, 1};
    auto q = PriorityQueueOfVector3D();
    for (const auto & v : x) {
        q.push(v);
    }
    for (auto i = 0u; i < x.size(); ++i) {
        const auto lhs = q.top();
        const auto rhs = x[sort_order[i]];
        CHECK(lhs == rhs);
        q.pop();
    }
}
