cmake_minimum_required(VERSION 2.8)

cmake_policy(SET CMP0015 NEW)

execute_process(COMMAND ln -s ../shaders)
execute_process(COMMAND ln -s ../images)
execute_process(COMMAND ln -s ../levels)

set(appName Minaria)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -O3 -DGLM_FORCE_RADIANS")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -g -DGLM_FORCE_RADIANS")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    MESSAGE( "64 bits compiler detected" )
    include_directories("SFML64/include")
    link_directories("SFML64/lib")
else( CMAKE_SIZEOF_VOID_P EQUAL 8 ) 
    MESSAGE( "32 bits compiler detected" )
    include_directories("SFML32/include")
    link_directories("SFML32/lib")
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(SOIL REQUIRED)
link_libraries(sfml-audio sfml-system)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLUT_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})
include_directories(${SOIL_INCLUDE_DIRS})

link_directories(${OPENGL_LIBRARY_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
link_directories(${SOIL_LIBRARY_DIRS})

add_executable(${appName} src/Player.h src/Player.cpp src/AnimKeyframes.h src/Sprite.h src/Sprite.cpp src/TileMap.h src/TileMap.cpp src/Texture.h src/Texture.cpp src/Scene.h src/Scene.cpp src/Shader.h src/Shader.cpp src/ShaderProgram.h src/ShaderProgram.cpp src/Game.h src/Game.cpp src/Block.h src/Block.cpp src/Camera.h src/Camera.cpp src/Enemy.h src/Enemy.cpp src/GroundEnemy.h src/GroundEnemy.cpp src/FlyingEnemy.h src/FlyingEnemy.cpp src/Character.h src/Character.cpp src/Inventory.h src/Inventory.cpp src/Item.h src/Item.cpp src/Rect.h src/Rect.cpp src/PerlinNoise.h src/PerlinNoise.cpp src/Tile.h src/Tile.cpp src/Text.h src/Text.cpp src/SceneGame.h src/SceneGame.cpp src/SceneMenu.h src/SceneMenu.cpp src/SceneCredits.h src/SceneCredits.cpp src/Background.h src/Background.cpp src/main.cpp src/ItemSword.h src/ItemSword.cpp src/ItemPickaxe.h src/ItemPickaxe.cpp src/CraftingBar.h src/CraftingBar.cpp src/ItemBomb.h src/ItemBomb.cpp src/Bomb.h src/Bomb.cpp src/ISceneNode.h src/ISceneNode.cpp src/BombExplosion.h src/BombExplosion.cpp src/SoundManager.h src/SoundManager.cpp src/TemporaryEffect.h src/TemporaryEffect.cpp src/Projectile.h src/Projectile.cpp src/WinSymbol.h src/WinSymbol.cpp src/SceneInstructions.h src/SceneInstructions.cpp)

target_link_libraries(${appName} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${SOIL_LIBRARIES} ${FREETYPE_LIBRARIES}) # ${GLM_LIBRARIES})



