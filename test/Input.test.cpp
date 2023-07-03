#include "SmallItem.hpp"
#include "Test.hpp"

#include <catch2/catch_test_macros.hpp>
#include <filesystem>

#include "input/InputFactory.hpp"

using namespace packing;

const auto data_dir = std::filesystem::path("test/data/Input/");

TEST_CASE("all cases", "[LargestFitFirst]") {
    const auto file_path = data_dir / "01.json";
    const auto input = InputFactory::create(file_path);
    SECTION("basic properties") {
        CHECK(input->type() == InputType::INPUT);
        CHECK(input->version() == InputVersion::V_0_3_0);
    }
    SECTION("small items") {
        const auto small_items = input->small_items();
        const auto expected = std::vector<SmallItem>{
            {Vector3D{3, 5, 7}},
            {Vector3D{6, 10, 14}},

        };
        CHECK(small_items == expected);
    }
    SECTION("small items quantity") {
        const auto small_items_quantity = input->small_items_quantity();
        const auto expected = std::vector<Quantity>{100, 200};
        CHECK(small_items_quantity == expected);
    }
}
