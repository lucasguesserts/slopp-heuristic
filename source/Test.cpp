#include "Test.hpp"

namespace Catch {

std::string StringMaker<packing::Vector3D>::convert(packing::Vector3D const & v) {
    return std::string("{") + std::to_string(v.x()) + std::string(", ") + std::to_string(v.y()) + std::string(", ") + std::to_string(v.z()) + std::string("}");
}

} // namespace Catch
