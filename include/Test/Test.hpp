#ifndef TEST_HPP_
#define TEST_HPP_

#include <catch2/catch_all.hpp>

#include <string>

#include "Geometry/Vector3D.hpp"

namespace Catch {

template <>
struct StringMaker<packing::Vector3D> {
    static std::string convert(packing::Vector3D const & v);
};

} // namespace Catch

#endif
