cmake_minimum_required(VERSION 3.15)
project(control C)

# Where you installed OSQP
set(OSQP_PREFIX "$ENV{HOME}/.local")
set(OSQP_INCLUDE_DIR "${OSQP_PREFIX}/include")
set(OSQP_LIB_DIR     "${OSQP_PREFIX}/lib")

# Sanity checks so we fail with a clear message if paths are wrong
if(NOT EXISTS "${OSQP_INCLUDE_DIR}/osqp/osqp.h")
  message(FATAL_ERROR "Can't find ${OSQP_INCLUDE_DIR}/osqp/osqp.h. \
Make sure OSQP is installed under ${OSQP_PREFIX} or adjust OSQP_PREFIX.")
endif()
if(NOT EXISTS "${OSQP_LIB_DIR}/libosqp.so" AND NOT EXISTS "${OSQP_LIB_DIR}/libosqp.a")
  message(FATAL_ERROR "Can't find libosqp in ${OSQP_LIB_DIR}. \
Make sure OSQP is installed under ${OSQP_PREFIX}.")
endif()

add_executable(controller src/test_osqp.c)

# Headers at ~/.local/include/osqp/osqp.h
target_include_directories(controller PRIVATE "${OSQP_INCLUDE_DIR}")

# Linker finds libosqp in ~/.local/lib
target_link_directories(controller PRIVATE "${OSQP_LIB_DIR}")
target_link_libraries(controller PRIVATE osqp)

# If you ever see unresolved QDLDL symbols, uncomment:
# target_link_libraries(controller PRIVATE qdldl)

# Make the exe find the shared lib at runtime without env vars
set_target_properties(controller PROPERTIES
  BUILD_RPATH "${OSQP_LIB_DIR}"
)

# (optional) emit compile_commands.json for debugging IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
