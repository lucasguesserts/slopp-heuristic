#ifndef MAXIMAL_EMPTY_SPACE_EMPTY_SPACE_HPP_
#define MAXIMAL_EMPTY_SPACE_EMPTY_SPACE_HPP_

#include <utility>
#include <memory>

#include "Geometry/Vector3D.hpp"

namespace packing {

namespace maximal_empty_space {

    class EmptySpace {
    public:
        EmptySpace() = default;
        ~EmptySpace() = default;
        virtual auto position() const -> Vector3D = 0;
        virtual auto measurement() const -> Vector3D = 0;
        virtual auto final_position() const -> Vector3D = 0;

        auto is_inside(const EmptySpace & other) const -> bool;

        virtual auto operator==(const EmptySpace & rhs) const -> bool;

        using Ptr = std::shared_ptr<EmptySpace>;
    };

} // namespace maximal_empty_space

} // namespace packing

#endif
