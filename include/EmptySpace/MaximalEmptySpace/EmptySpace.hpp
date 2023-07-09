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

        using Ptr = std::shared_ptr<EmptySpace>;
    };

    class BasicEmptySpace : public EmptySpace {
    public:
        BasicEmptySpace(const Vector3D position, const Vector3D measurement)
            : EmptySpace()
            , _position(std::move(position))
            , _measurement(std::move(measurement))
            , _final_position(position + measurement) {}

        using Ptr = std::shared_ptr<BasicEmptySpace>;

        auto position() const -> Vector3D override {
            return this->_position;
        }

        auto measurement() const -> Vector3D override {
            return this->_measurement;
        }

        auto final_position() const -> Vector3D override {
            return this->_final_position;
        }

    private:
        Vector3D _position;
        Vector3D _measurement;
        Vector3D _final_position;
    };

} // namespace maximal_empty_space

} // namespace packing

#endif
