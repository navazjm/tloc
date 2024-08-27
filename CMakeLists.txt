cmake_minimum_required(VERSION 3.10)
project(tloc VERSION 0.1.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

### Main Application Build ###
file(GLOB TLOC_SOURCES "src/*.c")
add_library(tloc_lib STATIC ${TLOC_SOURCES})  # Create a static library
target_compile_options(tloc_lib PRIVATE -Wall -Wextra -Werror)
target_include_directories(tloc_lib PUBLIC src)
add_executable(tloc "src/tloc.c")
target_link_libraries(tloc PRIVATE tloc_lib)  # Link the library to the executable

### AddressSanitizer Build ###
# same as main tloc build, but attach AddressSanitizer flags to check for possible memory leaks
add_executable(tloc_debug "src/tloc.c")
target_link_libraries(tloc_debug PRIVATE tloc_lib)
target_compile_options(tloc_debug PRIVATE -fsanitize=address -fno-omit-frame-pointer)
target_link_options(tloc_debug PRIVATE -fsanitize=address)
set_target_properties(tloc_debug PROPERTIES
    COMPILE_FLAGS "-fsanitize=address -fno-omit-frame-pointer"
    LINK_FLAGS "-fsanitize=address"
)

### Test Build ###
file(GLOB TLOC_TEST_SOURCES "tests/*.c")
add_executable(tloc_test ${TLOC_TEST_SOURCES})
target_compile_options(tloc_test PRIVATE -Wall -Wextra -Werror)
target_include_directories(tloc_test PRIVATE src tests vendors/munit)
target_sources(tloc_test PRIVATE vendors/munit/munit.c)
target_link_libraries(tloc_test PRIVATE tloc_lib)  # Link the library to the test executable


# allows user to run `sudo make tloc install` to create tloc executable and pace it in /usr/local/bin/ 
install(TARGETS tloc DESTINATION /usr/local/bin)
