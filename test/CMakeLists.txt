project(sfm_test)

find_package(Boost COMPONENTS unit_test_framework thread REQUIRED)
if(NOT Boost_USE_STATIC_LIBS)
#    add_definitions(-DBOOST_TEST_DYN_LINK)
endif()

add_executable(policy policy.cpp)
target_link_libraries(policy sfm ${Boost_LIBRARIES})
add_test(policy_test policy)

add_executable(variable variable.cpp)
target_link_libraries(variable sfm ${Boost_LIBRARIES})
add_test(variable_test variable)

add_executable(vartable vartable.cpp)
target_link_libraries(vartable sfm ${Boost_LIBRARIES})
add_test(vartable_test vartable)

add_executable(sl_variable sl_variable.cpp)
target_link_libraries(sl_variable sfm ${Boost_LIBRARIES})
add_test(sl_variable_test sl_variable)

add_executable(comporator comparator.cpp)
target_link_libraries(comporator sfm ${Boost_LIBRARIES})
add_test(comporator_test comporator)

add_executable(rule rule.cpp)
target_link_libraries(rule sfm ${Boost_LIBRARIES})
add_test(rule_test rule)
