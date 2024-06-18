file(GLOB SOURCES CONFIGURE_DEPENDS source/*.cpp)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(src ${SOURCES} "include/Tear.h" "source/Tear.cpp" "include/Level.h" "include/Patern.h" "source/Patern.cpp" "include/Goal.h" "source/Goal.cpp" "include/Tear_Basic.h" "source/Tear_Basic.cpp" "include/Projectile_Basic.h" "source/Projectile_Basic.cpp" "source/Projectile_Guided.cpp")
target_include_directories(src PUBLIC ./include)
target_link_libraries(src PUBLIC pugixml sfml-graphics)