file(GLOB SOURCES *.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(Tear main.cpp ${SOURCES})

target_link_libraries(Tear PUBLIC sfml-graphics)

add_custom_target(copy-resources ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/resources)
file(GLOB RESOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/resources/*)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/resources
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                            ${CMAKE_SOURCE_DIR}/resources
                            ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/resources)

add_dependencies(Tear copy-resources)
