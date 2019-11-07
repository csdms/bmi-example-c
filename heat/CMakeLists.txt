cmake_minimum_required(VERSION 3.0)

set (HEAT_VERSION 0.2)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/heatc.pc.cmake
                ${CMAKE_BINARY_DIR}/heat/heatc.pc)

if(WIN32)
  add_library(bmiheatc bmi_heat.c heat.c)
else()
  add_library(bmiheatc SHARED bmi_heat.c heat.c)
endif()

########### Heat main ###############

set (heat_sources main.c heat.c)
add_executable (run_heatc ${heat_sources})

########### Install files ###############

install(TARGETS run_heatc
  RUNTIME DESTINATION bin
  COMPONENT heat)
install(TARGETS bmiheatc
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  COMPONENT heat)
install(FILES bmi_heat.h
        DESTINATION include
        COMPONENT heat)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/heatc.pc
        DESTINATION lib/pkgconfig)
