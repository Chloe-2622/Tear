#
# Lines coming from https://github.com/google/googletest/tree/main/googletest#incorporating-into-an-existing-cmake-project
#

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
#   enable_testing()  already done in top CMakeLists.txt
add_executable(unitTests unitTests.cpp)
target_link_libraries(unitTests gtest_main)
target_link_libraries(unitTests src pugixml sfml-graphics sfml-audio)
add_test(NAME that-test-I-made COMMAND unitTests)

file(GLOB_RECURSE DYNAMIC_LIBS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/lib_openal32/${ARCH}/*.dll)
file(COPY ${DYNAMIC_LIBS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${DYNAMIC_LIBS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)

# add_custom_target(copy-resources ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/resources)
file(GLOB RESOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/resources/*)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/resources
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                            ${CMAKE_SOURCE_DIR}/resources
                            ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/resources)

add_dependencies(unitTests copy-resources)