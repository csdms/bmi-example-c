# heat

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/${model_name}.pc.cmake
  ${CMAKE_BINARY_DIR}/heat/${model_name}.pc
)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/${bmi_name}.pc.cmake
  ${CMAKE_BINARY_DIR}/heat/${bmi_name}.pc
)

if(WIN32)
  add_library(${model_name} heat.c)
  add_library(${bmi_name} bmi_heat.c heat.c)
else()
  add_library(${model_name} SHARED heat.c)
  add_library(${bmi_name} SHARED bmi_heat.c heat.c)
endif()

add_executable(run_${model_name} main.c heat.c)
add_executable(run_${bmi_name} bmi_main.c bmi_heat.c heat.c)

install(
  TARGETS run_${model_name} run_${bmi_name}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(
  TARGETS ${model_name} ${bmi_name}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(
  FILES bmi_heat.h heat.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${model_name}.pc
    ${CMAKE_CURRENT_BINARY_DIR}/${bmi_name}.pc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
