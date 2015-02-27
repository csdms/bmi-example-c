cmake_minimum_required(VERSION 2.6)

project (heat)

set (HEAT_VERSION 0.1)

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/heatc.pc.cmake
                ${CMAKE_CURRENT_SOURCE_DIR}/heatc.pc)

set (BUILD_SHARED_LIBS ON)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/.. )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set (bmi_heat_lib_SRCS bmi_heat.c heat.c)
add_library (bmi_heatc ${bmi_heat_lib_SRCS} )

########### Heat main ###############

set (heat_sources main.c heat.c)
add_executable (heatc ${heat_sources})

########### Install files ###############

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/heatc DESTINATION bin
  COMPONENT heat)
install(TARGETS bmi_heatc DESTINATION lib COMPONENT heat)
install(FILES bmi_heat.h
        DESTINATION include/heat
        COMPONENT heat)
install(FILES heatc.pc DESTINATION lib/pkgconfig)

