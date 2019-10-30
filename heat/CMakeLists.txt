cmake_minimum_required(VERSION 3.0)

set (HEAT_VERSION 0.2)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/heatc.pc.cmake
                ${CMAKE_BINARY_DIR}/heat/heatc.pc)

set (BUILD_SHARED_LIBS ON)

set (bmi_heat_lib_SRCS bmi_heat.c heat.c)
add_library (bmiheatc ${bmi_heat_lib_SRCS} )

########### Heat main ###############

set (heat_sources main.c heat.c)
add_executable (heatc ${heat_sources})

########### Install files ###############

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/heatc DESTINATION bin
  COMPONENT heat)
install(TARGETS bmiheatc DESTINATION lib COMPONENT heat)
install(FILES bmi_heat.h
        DESTINATION include
        COMPONENT heat)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/heatc.pc
        DESTINATION lib/pkgconfig)
