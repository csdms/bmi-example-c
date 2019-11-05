cmake_minimum_required(VERSION 3.0)

include (CTest)

add_test (BMI_IRF test_irf)
add_test (BMI_VAR_NAMES test_print_var_names)
add_test (BMI_GET_VALUES test_get_value)
add_test (BMI_SET_VALUES test_set_value)
add_test (BMI_GRID_INFO test_grid_info)
add_test (BMI_REINITIALIZE test_reinitialize)
add_test (BMI_CONFLICTING_INSTANCES test_conflicting_instances)
add_test (BMI_INITIALIZE_FROM_FILE test_initialize_from_file)

set (BUILD_SHARED_LIBS ON)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../heat )

########### BMI main program ###############

set (bmi_irf_SRCS test_irf.c)
set (bmi_var_names_SRCS test_print_var_names.c)
set (bmi_get_value_SRCS test_get_value.c)
set (bmi_set_value_SRCS test_set_value.c)
set (bmi_grid_info_SRCS test_grid_info.c)
set (bmi_reinitialize_SRCS test_reinitialize.c)
set (bmi_conflicting_instances_SRCS test_conflicting_instances.c)
set (bmi_initialize_from_file_SRCS test_initialize_from_file.c)

add_executable(test_irf ${bmi_irf_SRCS})
add_executable(test_print_var_names ${bmi_var_names_SRCS})
add_executable(test_get_value ${bmi_get_value_SRCS})
add_executable(test_set_value ${bmi_set_value_SRCS})
add_executable(test_grid_info ${bmi_grid_info_SRCS})
add_executable(test_reinitialize ${bmi_reinitialize_SRCS})
add_executable(test_conflicting_instances ${bmi_conflicting_instances_SRCS})
add_executable(test_initialize_from_file ${bmi_initialize_from_file_SRCS})

target_link_libraries(test_irf bmiheatc)
target_link_libraries(test_print_var_names bmiheatc)
target_link_libraries(test_get_value bmiheatc)
target_link_libraries(test_set_value bmiheatc)
target_link_libraries(test_grid_info bmiheatc)
target_link_libraries(test_reinitialize bmiheatc)
target_link_libraries(test_conflicting_instances bmiheatc)
target_link_libraries(test_initialize_from_file bmiheatc)

file(
  COPY ${CMAKE_CURRENT_SOURCE_DIR}/config.txt
  DESTINATION ${CMAKE_BINARY_DIR}/testing)
