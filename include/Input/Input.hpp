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

class Input_V_0_3_0 : public Input {
public:
    Input_V_0_3_0(const nlohmann::json & data)
        : Input(data) {}
    ~Input_V_0_3_0() = default;
};

class InputFactory {
public:
    static auto create(const std::string file_path) -> InputPtr;

private:
    static auto load_json(const std::string file_path) -> nlohmann::json;
};

} // namespace packing

#endif
