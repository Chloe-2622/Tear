file(GLOB SOURCES CONFIGURE_DEPENDS source/*.cpp)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(src ${SOURCES}
	source/GameObjects/GameObject.cpp
	source/GameObjects/Player.cpp
	source/GameObjects/Projectiles/Projectile.cpp
	source/GameObjects/Projectiles/Projectile_Basic.cpp
	source/GameObjects/Projectiles/Projectile_Guided.cpp
	source/GameObjects/Tears/Tear.cpp
	source/GameObjects/Tears/Tear_Basic.cpp
	source/GameObjects/Tears/Tear_Guided.cpp
	source/GameObjects/Tears/Tear_River.cpp
	source/Scenes/Level.cpp
	source/Scenes/Menu.cpp
	source/Scenes/Shop.cpp
	source/Scenes/Victory.cpp
	source/Game.cpp
	source/Goal.cpp
	source/myMain.cpp
	source/Patern.cpp
	source/ResourceManager.cpp

	include/GameObjects/GameObject.h
	include/GameObjects/Player.h
	include/GameObjects/Projectiles/Projectile.h
	include/GameObjects/Projectiles/Projectile_Basic.h
	include/GameObjects/Projectiles/Projectile_Guided.h
	include/GameObjects/Tears/Tear.h
	include/GameObjects/Tears/Tear_Basic.h
	include/GameObjects/Tears/Tear_Guided.h
	include/GameObjects/Tears/Tear_River.h
	include/Scenes/Level.h
	include/Scenes/Menu.h
	include/Scenes/Shop.h
	source/Scenes/Victory.h
	include/Game.hpp
	include/Goal.h
	include/myMain.h
	include/Patern.h
	include/ResourceManager.h)

target_include_directories(src PUBLIC ./include)
target_link_libraries(src PUBLIC pugixml sfml-graphics sfml-audio)