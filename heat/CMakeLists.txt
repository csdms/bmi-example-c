cmake_minimum_required(VERSION 3.12)

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

add_executable (run_bmiheatc bmi_main.c bmi_heat.c heat.c)

########### Install files ###############

install(TARGETS run_heatc run_bmiheatc
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  COMPONENT heat)
install(TARGETS bmiheatc
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  COMPONENT heat)
install(FILES bmi_heat.h heat.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT heat)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/heatc.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
