# bmi-example-c

cmake_minimum_required(VERSION 3.12)
project(bmi-example-c
  VERSION 2.0.3
  LANGUAGES C
)

include(GNUInstallDirs)

set(model_name heatc)
set(bmi_name bmi${model_name})

set(_cflags "-ansi -Wall -Wundef -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -O2")
if(NOT WIN32)
  if(CMAKE_C_FLAGS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${_cflags}")
  else()
    set(CMAKE_C_FLAGS ${_cflags})
  endif()
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(BMIC REQUIRED IMPORTED_TARGET bmic)
message("--   bmic include dir - ${BMIC_INCLUDE_DIRS}")
include_directories(${BMIC_INCLUDE_DIRS})

add_subdirectory(heat)
add_subdirectory(testing)

include(CTest)
