#include <catch2/catch_test_macros.hpp>

#include "BoolMatrix.hpp"

using namespace packing;

TEST_CASE("constructor", "[BoolMatrix]") {
    const auto number_of_rows = Index{5};
    const auto number_of_columns = Index{7};
    const auto matrix = BoolMatrix{number_of_rows, number_of_columns};
    CHECK(matrix.number_of_rows() == number_of_rows);
    CHECK(matrix.number_of_columns() == number_of_columns);
    for (auto i = 0u; i < number_of_rows; ++i) {
        for (auto j = 0u; j < number_of_columns; ++j) {
            CHECK_FALSE(matrix(i, j));
        }
    }
}
