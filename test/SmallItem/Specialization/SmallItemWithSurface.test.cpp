#include "Test/Test.hpp"

#include "Geometry/Surface.hpp"
#include "Geometry/Vector3D.hpp"
#include "SmallItem/Specialization/SmallItemWithSurface.hpp"

using namespace packing;

TEST_CASE("surface", "[AllocatedSmallItem]") {
    // measurement
    const auto size_x = CoordinateType{2};
    const auto size_y = CoordinateType{3};
    const auto size_z = CoordinateType{5};
    const auto measurement = Vector3D{size_x, size_y, size_z};
    const auto quantity = Quantity{7};
    // item
    const auto small_item = SmallItemWithSurface{measurement, quantity};
    // expected surface
    const auto expected = Surface{
        {0, 0, -1},
        {0, 1, -1},
        {0, 2, -1},
        {1, 0, -1},
        {1, 1, -1},
        {1, 2, -1},
        {0, 0, 5},
        {0, 1, 5},
        {0, 2, 5},
        {1, 0, 5},
        {1, 1, 5},
        {1, 2, 5},
        {0, -1, 0},
        {0, -1, 1},
        {0, -1, 2},
        {0, -1, 3},
        {0, -1, 4},
        {1, -1, 0},
        {1, -1, 1},
        {1, -1, 2},
        {1, -1, 3},
        {1, -1, 4},
        {0, 3, 0},
        {0, 3, 1},
        {0, 3, 2},
        {0, 3, 3},
        {0, 3, 4},
        {1, 3, 0},
        {1, 3, 1},
        {1, 3, 2},
        {1, 3, 3},
        {1, 3, 4},
        {-1, 0, 0},
        {-1, 0, 1},
        {-1, 0, 2},
        {-1, 0, 3},
        {-1, 0, 4},
        {-1, 1, 0},
        {-1, 1, 1},
        {-1, 1, 2},
        {-1, 1, 3},
        {-1, 1, 4},
        {-1, 2, 0},
        {-1, 2, 1},
        {-1, 2, 2},
        {-1, 2, 3},
        {-1, 2, 4},
        {2, 0, 0},
        {2, 0, 1},
        {2, 0, 2},
        {2, 0, 3},
        {2, 0, 4},
        {2, 1, 0},
        {2, 1, 1},
        {2, 1, 2},
        {2, 1, 3},
        {2, 1, 4},
        {2, 2, 0},
        {2, 2, 1},
        {2, 2, 2},
        {2, 2, 3},
        {2, 2, 4}};
    // check
    CHECK(small_item.surface() == expected);
}
