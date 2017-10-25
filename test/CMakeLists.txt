cmake_minimum_required(VERSION 2.8)
project(LOGOL_TEST)

include_directories(${LOGOL_SOURCE_DIR}/include)

# Add lib
LINK_DIRECTORIES(${LOGOL_BINARY_DIR})
set( DEPS "${DEPS};logol" )

# Add Catch
INCLUDE_DIRECTORIES( ${LOGOL_TEST_SOURCE_DIR}/Catch/single_include/ )

# Global shit
file (GLOB_RECURSE LOGOL_TEST_SRC ./*.cc)
add_executable(logol_test ${LOGOL_TEST_SRC})

target_link_libraries ( logol_test ${DEPS} )
