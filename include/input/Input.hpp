#ifndef INPUT_HPP_
#define INPUT_HPP_

#include <memory>
#include <string>

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
    Input(const nlohmann::json & data);
    ~Input() = default;

    auto type() const -> InputType;
    auto version() const -> InputVersion;

protected:
    const nlohmann::json data;
};

using InputPtr = std::unique_ptr<Input>;

} // namespace packing

#endif
