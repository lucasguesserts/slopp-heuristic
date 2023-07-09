project(test)

set(TEST_EXECUTABLE "run_tests")

include_directories(${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/)

set(
    TEST_CASE_SOURCE_LIST
    Dependency/json.test.cpp
    Timer/Timer.cpp
    Geometry/Vector3D.test.cpp
    Algorithm/LargestFitFirst.test.cpp
    Algorithm/LargestFitFirstV2.test.cpp
    SmallItem/BasicSmallItem.test.cpp
    SmallItem/Specialization/SmallItemWithSurface.test.cpp
    SmallItem/Container/QuantityManager.test.cpp
    SmallItem/Container/OrderedSmallItemsByVolume.test.cpp
    AllocatedSmallItem/BasicAllocatedSmallItem.test.cpp
    AllocatedSmallItem/Specialization/AllocatedSmallItemWithSurface.test.cpp
    LargeObject/BasicLargeObject.test.cpp
    EmptySpace/MaximalEmptySpace/M_EmptySpace.test.cpp
    Input/Specialization/BasicInput.test.cpp
    Algorithm/LargestFitFirst/BoolCuboid.test.cpp
    Algorithm/LargestFitFirst/CornerPointIdentifier.test.cpp
    Algorithm/LargestFitFirst/PriorityQueueOfVector3D.test.cpp
)

foreach(TEST_CASE_SOURCE IN ITEMS ${TEST_CASE_SOURCE_LIST})
    cmake_path(GET TEST_CASE_SOURCE STEM LAST_ONLY TEST_CASE_NAME)
    add_executable(${TEST_CASE_NAME} ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/${TEST_CASE_SOURCE})
    add_test(NAME ${TEST_CASE_NAME} COMMAND ${TEST_CASE_NAME} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
    target_link_libraries(${TEST_CASE_NAME} PRIVATE ${PROJECT_LIBRARY} PRIVATE Catch2::Catch2WithMain)
endforeach()
