#ifndef BOOL_MATRIX_HPP_
#define BOOL_MATRIX_HPP_

#include <cstddef>
#include <utility>
#include <vector>

namespace packing {

using Index = std::size_t;
using Entry = std::pair<Index, Index>;

class BoolMatrix {
public:
    BoolMatrix(const Index number_of_rows, const Index number_of_columns);

    [[nodiscard]] auto number_of_rows() const -> Index {
        return this->_number_of_rows;
    }

    [[nodiscard]] auto number_of_columns() const -> Index {
        return this->_number_of_columns;
    }

    [[nodiscard]] auto data() -> std::vector<std::vector<bool>> & {
        return this->_data;
    }
    [[nodiscard]] auto data() const -> const std::vector<std::vector<bool>> & {
        return this->_data;
    }

    auto operator()(const Index & row, const Index & column) const -> bool {
        return this->data()[row][column];
    }

private:
    const Index _number_of_rows;
    const Index _number_of_columns;
    std::vector<std::vector<bool>> _data;
};

} // namespace packing

#endif
