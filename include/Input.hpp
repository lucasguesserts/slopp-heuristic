#ifndef INPUT_HPP_
#define INPUT_HPP_

#include <string>
#include <stdexcept>

#include <nlohmann/json.hpp>

namespace packing {

enum class InputType {
    INPUT,
    OUTPUT
};

enum class InputVersion {
    V_0_3_0
};

class Input {
public:
    Input(const std::string file_path);

    auto type() const -> InputType;
    auto version() const -> InputVersion;

private:
    const nlohmann::json data;

    static auto load_json(const std::string file_path) -> nlohmann::json;

};

} // namespace packing

#endif
