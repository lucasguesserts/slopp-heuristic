#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

#include "LargestFitFirstAlgorithm.hpp"

using std::cout;
using std::endl;
using std::string;

using json = nlohmann::json;

using namespace packing;

auto main(int argc, char * argv[]) -> int {
    const auto program_name = string(argv[0]);
    if (argc != 2) {
        cout
            << "Usage:" << endl
            << "    " << program_name << " INPUT" << endl
            << "    "
            << "INPUT is a json file specifying the input of the problem" << endl;
        return 1;
    }
    const auto input_file_path = std::filesystem::path(argv[1]);
    std::ifstream file(input_file_path);
    const json data = json::parse(file);
    file.close();
    auto algorithm = LargestFitFirstAlgorithm::from_json(data);
    algorithm.allocate();
    const auto output = LargestFitFirstAlgorithm::to_json(algorithm);
    cout << output.dump(2);
    return 0;
}
