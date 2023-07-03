#include "Test.hpp"

#include <catch2/catch_test_macros.hpp>
#include <filesystem>

#include "input/InputFactory.hpp"

using namespace packing;

const auto data_dir = std::filesystem::path("test/data/Input/");

TEST_CASE("all cases", "[LargestFitFirst]") {
    const auto file_path = data_dir / "01.json";
    const auto input = InputFactory::create(file_path);
    CHECK(input->type() == InputType::INPUT);
    CHECK(input->version() == InputVersion::V_0_3_0);
}
