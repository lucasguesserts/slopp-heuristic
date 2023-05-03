#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

#include "LargestFitFirstAlgorithm.hpp"

using json = nlohmann::json;

using namespace packing;

auto main(int argc, char * argv[]) -> int {
    // CLI args
    const auto program_name = std::string(argv[0]);
    if (argc != 3) {
        std::cerr
            << "Usage:" << std::endl
            << "    " << program_name << " INPUT" << " " << "OUTPUT" << std::endl
            << "    " << "INPUT is a json file specifying the input of the problem" << std::endl
            << "    " << "OUTPUT is the file to save the output" << std::endl
        ;
        return 1;
    }
    const auto input_file_path = std::filesystem::path(argv[1]);
    const auto output_file_path = std::filesystem::path(argv[2]);
    const auto output_dir = output_file_path.parent_path();
    std::filesystem::create_directories(output_dir);

    // input data
    std::ifstream input_file(input_file_path);
    const json data = json::parse(input_file);
    input_file.close();

    // solve
    auto algorithm = LargestFitFirstAlgorithm::from_json(data);
    algorithm.allocate();

    // output
    const auto output = LargestFitFirstAlgorithm::to_json(algorithm);
    std::ofstream output_file(output_file_path);
    output_file << output.dump(2);
    output_file.close();

    return 0;
}
