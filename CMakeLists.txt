project(safety_master)
cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${Boost_INCLUDE_DIR} -L${Boost_LIBRARY_DIR}")

aux_source_directory(src SOURCE)
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
