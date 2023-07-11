#include "Test/Test.hpp"

#include "EmptySpace/MaximalEmptySpace/EmptySpace.hpp"
#include "EmptySpace/MaximalEmptySpace/Specialization/BasicEmptySpace.hpp"
#include "Geometry/Vector3D.hpp"

using namespace packing;
using namespace packing::maximal_empty_space;

TEST_CASE("EmptySpace", "[EmptySpace]") {
    const auto position = Vector3D{3, 5, 7};
    const auto measurement = Vector3D{11, 13, 17};
    const auto final_position = Vector3D{14, 18, 24};
    const EmptySpace::Ptr empty_space = std::make_shared<BasicEmptySpace>(position, measurement);
    CHECK(empty_space->position() == position);
    CHECK(empty_space->measurement() == measurement);
    CHECK(empty_space->final_position() == final_position);
}

TEST_CASE("is_inside", "[EmptySpace]") {
    const auto position = Vector3D{3, 5, 7};
    const auto measurement = Vector3D{11, 13, 17};
    const EmptySpace::Ptr empty_space = std::make_shared<BasicEmptySpace>(position, measurement);
    SECTION("same measurements") {
        const auto other_position = Vector3D{3, 5, 7};
        const auto other_measurement = Vector3D{11, 13, 17};
        const EmptySpace::Ptr other_empty_space = std::make_shared<BasicEmptySpace>(other_position, other_measurement);
        CHECK(empty_space->is_inside(*other_empty_space));
        CHECK(other_empty_space->is_inside(*empty_space));
    }
    SECTION("completely within") {
        const auto other_position = Vector3D{4, 6, 8};
        const auto other_measurement = Vector3D{1, 2, 3};
        const EmptySpace::Ptr other_empty_space = std::make_shared<BasicEmptySpace>(other_position, other_measurement);
        CHECK_FALSE(empty_space->is_inside(*other_empty_space));
        CHECK(other_empty_space->is_inside(*empty_space));
    }
    SECTION("out") {
        const auto other_position = Vector3D{1, 5, 7};
        const auto other_measurement = Vector3D{11, 13, 17};
        const EmptySpace::Ptr other_empty_space = std::make_shared<BasicEmptySpace>(other_position, other_measurement);
        CHECK_FALSE(empty_space->is_inside(*other_empty_space));
        CHECK_FALSE(other_empty_space->is_inside(*empty_space));
    }
}
