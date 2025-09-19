cmake_minimum_required(VERSION 3.20)
project(control C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Build OSQP statically (flip to ON if you want shared)
set(BUILD_SHARED_LIBS OFF)
option(OSQP_ENABLE_PROFILING "Enable OSQP profiling" OFF)
option(OSQP_ENABLE_OPENMP    "Enable OpenMP in OSQP"   OFF)

# Bring in OSQP from submodule
add_subdirectory(external/osqp EXCLUDE_FROM_ALL)

# Pick the right OSQP target name
if(TARGET osqpstatic)
  set(OSQP_TGT osqpstatic)
else()
  set(OSQP_TGT osqp)
endif()

# Your headers (so IntelliSense & compiler see include/)
add_library(project_headers INTERFACE)
target_include_directories(project_headers INTERFACE
  ${CMAKE_SOURCE_DIR}/include
)

# ---- Executable 1: main app ----
add_executable(control
  src/main.c
  src/utils.c          # <-- implement next_2_power here
)
target_link_libraries(control PRIVATE ${OSQP_TGT} project_headers)
if(UNIX AND NOT APPLE)
  target_link_libraries(control PRIVATE m)  # for sqrt()
endif()

# ---- Executable 2: OSQP test ----
add_executable(test_osqp
  src/test_osqp.c
  src/utils.c
)
target_link_libraries(test_osqp PRIVATE ${OSQP_TGT} project_headers)
if(UNIX AND NOT APPLE)
  target_link_libraries(test_osqp PRIVATE m)
endif()
