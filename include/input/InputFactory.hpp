#ifndef INPUT_FACTORY_HPP_
#define INPUT_FACTORY_HPP_

#include "input/Input.hpp"

#include <nlohmann/json.hpp>

namespace packing {

class InputFactory {
public:
    static auto create(const std::string file_path) -> InputPtr;

private:
    static auto load_json(const std::string file_path) -> nlohmann::json;
};

} // namespace packing

#endif
