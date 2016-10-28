cmake_minimum_required(VERSION 2.8)

cmake_policy(SET CMP0015 NEW)

execute_process(COMMAND ln -s ../shaders)
execute_process(COMMAND ln -s ../images)
execute_process(COMMAND ln -s ../levels)

set(appName TerrariaLinux)

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -O3 -DGLM_FORCE_RADIANS")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -g -DGLM_FORCE_RADIANS")

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

add_executable(${appName} Player.h Player.cpp AnimKeyframes.h Sprite.h Sprite.cpp TileMap.h TileMap.cpp Texture.h Texture.cpp Scene.h Scene.cpp Shader.h Shader.cpp ShaderProgram.h ShaderProgram.cpp Game.h Game.cpp Block.h Block.cpp Camera.h Camera.cpp Enemy.h Enemy.cpp GroundEnemy.h GroundEnemy.cpp FlyingEnemy.h FlyingEnemy.cpp Character.h Character.cpp Inventory.h Inventory.cpp Item.h Item.cpp Rect.h Rect.cpp PerlinNoise.h PerlinNoise.cpp Tile.h Tile.cpp Text.h Text.cpp SceneGame.h SceneGame.cpp SceneMenu.h SceneMenu.cpp SceneCredits.h SceneCredits.cpp Background.h Background.cpp main.cpp ItemSword.h ItemSword.cpp ItemPickaxe.h ItemPickaxe.cpp CraftingBar.h CraftingBar.cpp ItemBomb.h ItemBomb.cpp Bomb.h Bomb.cpp ISceneNode.h ISceneNode.cpp BombExplosion.h BombExplosion.cpp SoundManager.h SoundManager.cpp TemporaryEffect.h TemporaryEffect.cpp Projectile.h Projectile.cpp WinSymbol.h WinSymbol.cpp)

target_link_libraries(${appName} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${SOIL_LIBRARIES} ${FREETYPE_LIBRARIES}) # ${GLM_LIBRARIES})



