#include "BoolMatrix.hpp"

#include <utility>
#include <vector>

namespace packing {

BoolMatrix::BoolMatrix(const Index number_of_rows, const Index number_of_columns)
    : _number_of_rows(std::move(number_of_rows))
    , _number_of_columns(std::move(number_of_columns))
    , _data(number_of_rows, std::vector<bool>(number_of_columns, false)) {}

} // namespace packing
