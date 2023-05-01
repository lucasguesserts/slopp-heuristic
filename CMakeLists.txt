CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

project(
    dynamic-programming
    VERSION 0.0.0
    HOMEPAGE_URL "https://github.com/lucasguesserts/slopp-heuristic"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic-errors -fmax-errors=1 --coverage -Wno-error=ignored-qualifiers")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic-errors -ferror-limit=1 --coverage")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

find_package(Catch2 3 REQUIRED)

set(PROJECT_LIBRARY ${PROJECT_NAME})
set(HEADER_DIR ${CMAKE_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)

set(
    PROJECT_SOURCE_FILES
    ${SOURCE_DIR}/SmallItem.cpp
)

add_library(${PROJECT_LIBRARY} SHARED ${PROJECT_SOURCE_FILES})

include_directories(${HEADER_DIR})

enable_testing()
add_subdirectory(test)
add_subdirectory(benchmark)

message("\n")
message("---- Project ${PROJECT_NAME} ----")
message("Version               = ${PROJECT_VERSION}")
message("Description           = ${PROJECT_DESCRIPTION}")
message("Homepage              = ${PROJECT_HOMEPAGE_URL}")
message("C++ compiler	       = ${CMAKE_CXX_COMPILER}")
message("Compiler flags	       = ${CMAKE_CXX_FLAGS}")
message("Compiler version      = ${CMAKE_CXX_COMPILER_VERSION}")
message("\n")
