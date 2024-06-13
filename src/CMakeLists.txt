file(GLOB SOURCES CONFIGURE_DEPENDS source/*.cpp)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(src ${SOURCES})
target_include_directories(src PUBLIC ./include)
target_link_libraries(src PUBLIC pugixml sfml-graphics)