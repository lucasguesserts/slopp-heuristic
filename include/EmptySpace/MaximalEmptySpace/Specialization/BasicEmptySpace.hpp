#ifndef MAXIMAL_EMPTY_SPACE_BASIC_EMPTY_SPACE_HPP_
#define MAXIMAL_EMPTY_SPACE_BASIC_EMPTY_SPACE_HPP_

#include "EmptySpace/MaximalEmptySpace/EmptySpace.hpp"

namespace packing {

namespace maximal_empty_space {

    class BasicEmptySpace : public EmptySpace {
    public:
        BasicEmptySpace(const Vector3D position, const Vector3D measurement);
        ~BasicEmptySpace() = default;

        auto position() const -> Vector3D override;
        auto measurement() const -> Vector3D override;
        auto final_position() const -> Vector3D override;

        using Ptr = std::shared_ptr<BasicEmptySpace>;

    private:
        Vector3D _position;
        Vector3D _measurement;
        Vector3D _final_position;
    };

} // namespace maximal_empty_space

} // namespace packing

#endif
