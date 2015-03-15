project(safety_master)
cmake_minimum_required(VERSION 2.8)

include(CTest)
include_directories(src)

find_package(Boost COMPONENTS chrono system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

file(GLOB SOURCE src/*.cpp)
list(REMOVE_ITEM SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_library(sfm ${SOURCE})
target_link_libraries(sfm ${Boost_LIBRARIES})

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} sfm)

if(WIN32)
	find_library(WSOCK32_LIBRARY wsock32)
	find_library(WS2_32_LIBRARY ws2_32)
	target_link_libraries(sfm ${WSOCK32_LIBRARY} ${WS2_32_LIBRARY})
endif(WIN32)

add_subdirectory(test)