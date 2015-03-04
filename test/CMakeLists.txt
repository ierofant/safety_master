project(sfm_test)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(policy policy.cpp)
target_link_libraries(policy sfm ${Boost_LIBRARIES})
add_test(policy_test policy)

add_executable(variable variable.cpp)
target_link_libraries(variable sfm ${Boost_LIBRARIES})
add_test(variable_test variable)