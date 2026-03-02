cmake_minimum_required(VERSION 3.18)
project(ta_cross_language_c C)

# Find the parent TA-Lib build
set(TALIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../..")
set(TALIB_BUILD "${TALIB_ROOT}/cmake-build")

add_executable(cross_lang_c main.c)

target_include_directories(cross_lang_c PRIVATE
    "${TALIB_ROOT}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

# Link against the static library built by the parent project
find_library(TALIB_STATIC
    NAMES ta-lib
    PATHS "${TALIB_BUILD}/lib" "${TALIB_BUILD}"
    NO_DEFAULT_PATH
)

if(NOT TALIB_STATIC)
    message(FATAL_ERROR "Could not find ta-lib static library in ${TALIB_BUILD}. Build the main project first.")
endif()

target_link_libraries(cross_lang_c PRIVATE ${TALIB_STATIC})

if(NOT WIN32)
    target_link_libraries(cross_lang_c PRIVATE m)
endif()
