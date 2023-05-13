#include "Test.hpp"

#include "Vector3D.hpp"
#include "PriorityQueueOfVector3D.hpp"

#include <vector>

using namespace packing;

TEST_CASE("less", "[PriorityQueueOfVector3D]") {
    const auto less = LessVector3D();
    SECTION("true") {
        CHECK(less({9, 9, 0}, {1, 2, 3}));
        CHECK(less({0, 9, 3}, {1, 2, 3}));
        CHECK(less({1, 0, 3}, {1, 2, 3}));

        CHECK(less({0, 2, 3}, {1, 0, 3}));
        CHECK(less({1, 2, 0}, {0, 0, 1}));
    }
    SECTION("false") {
        CHECK_FALSE(less({1, 2, 3}, {9, 9, 0}));
        CHECK_FALSE(less({1, 2, 3}, {0, 9, 3}));
        CHECK_FALSE(less({1, 2, 3}, {1, 0, 3}));

        CHECK_FALSE(less({1, 0, 3}, {0, 2, 3}));
        CHECK_FALSE(less({0, 0, 1}, {1, 2, 0}));

        CHECK_FALSE(less({1, 2, 3}, {1, 2, 3}));
        CHECK_FALSE(less({1, 2, 9}, {9, 9, 3}));
        CHECK_FALSE(less({9, 2, 3}, {1, 9, 3}));
        CHECK_FALSE(less({1, 9, 3}, {1, 2, 3}));
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
