#ifndef SIZE_HPP_
#define SIZE_HPP_

namespace packing {

using SizeType = unsigned;

class Size {
public:
    Size(const SizeType x, const SizeType y, const SizeType z);

    [[nodiscard]] auto x() const -> SizeType {
        return this->_x;
    }
    [[nodiscard]] auto y() const -> SizeType {
        return this->_y;
    }
    [[nodiscard]] auto z() const -> SizeType {
        return this->_z;
    }

private:
    const SizeType _x;
    const SizeType _y;
    const SizeType _z;
};

} // namespace packing

#endif
