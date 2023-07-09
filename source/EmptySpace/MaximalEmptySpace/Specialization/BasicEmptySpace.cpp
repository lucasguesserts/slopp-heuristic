#include "EmptySpace/MaximalEmptySpace/Specialization/BasicEmptySpace.hpp"

namespace packing {

namespace maximal_empty_space {

    BasicEmptySpace::BasicEmptySpace(const Vector3D position, const Vector3D measurement)
        : EmptySpace()
        , _position(std::move(position))
        , _measurement(std::move(measurement))
        , _final_position(position + measurement) {}

    auto BasicEmptySpace::position() const -> Vector3D {
        return this->_position;
    }

    auto BasicEmptySpace::measurement() const -> Vector3D {
        return this->_measurement;
    }

    auto BasicEmptySpace::final_position() const -> Vector3D {
        return this->_final_position;
    }

} // namespace maximal_empty_space

} // namespace packing
