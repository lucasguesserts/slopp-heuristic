#include "Test/Test.hpp"

#include "Geometry/Vector3D.hpp"
#include "EmptySpace/MaximalEmptySpace/EmptySpace.hpp"

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
