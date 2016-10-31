# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sephirot47/Minaria

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sephirot47/Minaria

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running interactive CMake command-line interface..."
	/usr/bin/cmake -i .
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sephirot47/Minaria/CMakeFiles /home/sephirot47/Minaria/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sephirot47/Minaria/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Minaria

# Build rule for target.
Minaria: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Minaria
.PHONY : Minaria

# fast build rule for target.
Minaria/fast:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/build
.PHONY : Minaria/fast

src/Background.o: src/Background.cpp.o
.PHONY : src/Background.o

# target to build an object file
src/Background.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Background.cpp.o
.PHONY : src/Background.cpp.o

src/Background.i: src/Background.cpp.i
.PHONY : src/Background.i

# target to preprocess a source file
src/Background.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Background.cpp.i
.PHONY : src/Background.cpp.i

src/Background.s: src/Background.cpp.s
.PHONY : src/Background.s

# target to generate assembly for a file
src/Background.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Background.cpp.s
.PHONY : src/Background.cpp.s

src/Block.o: src/Block.cpp.o
.PHONY : src/Block.o

# target to build an object file
src/Block.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Block.cpp.o
.PHONY : src/Block.cpp.o

src/Block.i: src/Block.cpp.i
.PHONY : src/Block.i

# target to preprocess a source file
src/Block.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Block.cpp.i
.PHONY : src/Block.cpp.i

src/Block.s: src/Block.cpp.s
.PHONY : src/Block.s

# target to generate assembly for a file
src/Block.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Block.cpp.s
.PHONY : src/Block.cpp.s

src/Bomb.o: src/Bomb.cpp.o
.PHONY : src/Bomb.o

# target to build an object file
src/Bomb.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Bomb.cpp.o
.PHONY : src/Bomb.cpp.o

src/Bomb.i: src/Bomb.cpp.i
.PHONY : src/Bomb.i

# target to preprocess a source file
src/Bomb.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Bomb.cpp.i
.PHONY : src/Bomb.cpp.i

src/Bomb.s: src/Bomb.cpp.s
.PHONY : src/Bomb.s

# target to generate assembly for a file
src/Bomb.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Bomb.cpp.s
.PHONY : src/Bomb.cpp.s

src/BombExplosion.o: src/BombExplosion.cpp.o
.PHONY : src/BombExplosion.o

# target to build an object file
src/BombExplosion.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/BombExplosion.cpp.o
.PHONY : src/BombExplosion.cpp.o

src/BombExplosion.i: src/BombExplosion.cpp.i
.PHONY : src/BombExplosion.i

# target to preprocess a source file
src/BombExplosion.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/BombExplosion.cpp.i
.PHONY : src/BombExplosion.cpp.i

src/BombExplosion.s: src/BombExplosion.cpp.s
.PHONY : src/BombExplosion.s

# target to generate assembly for a file
src/BombExplosion.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/BombExplosion.cpp.s
.PHONY : src/BombExplosion.cpp.s

src/Camera.o: src/Camera.cpp.o
.PHONY : src/Camera.o

# target to build an object file
src/Camera.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Camera.cpp.o
.PHONY : src/Camera.cpp.o

src/Camera.i: src/Camera.cpp.i
.PHONY : src/Camera.i

# target to preprocess a source file
src/Camera.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Camera.cpp.i
.PHONY : src/Camera.cpp.i

src/Camera.s: src/Camera.cpp.s
.PHONY : src/Camera.s

# target to generate assembly for a file
src/Camera.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Camera.cpp.s
.PHONY : src/Camera.cpp.s

src/Character.o: src/Character.cpp.o
.PHONY : src/Character.o

# target to build an object file
src/Character.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Character.cpp.o
.PHONY : src/Character.cpp.o

src/Character.i: src/Character.cpp.i
.PHONY : src/Character.i

# target to preprocess a source file
src/Character.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Character.cpp.i
.PHONY : src/Character.cpp.i

src/Character.s: src/Character.cpp.s
.PHONY : src/Character.s

# target to generate assembly for a file
src/Character.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Character.cpp.s
.PHONY : src/Character.cpp.s

src/CraftingBar.o: src/CraftingBar.cpp.o
.PHONY : src/CraftingBar.o

# target to build an object file
src/CraftingBar.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/CraftingBar.cpp.o
.PHONY : src/CraftingBar.cpp.o

src/CraftingBar.i: src/CraftingBar.cpp.i
.PHONY : src/CraftingBar.i

# target to preprocess a source file
src/CraftingBar.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/CraftingBar.cpp.i
.PHONY : src/CraftingBar.cpp.i

src/CraftingBar.s: src/CraftingBar.cpp.s
.PHONY : src/CraftingBar.s

# target to generate assembly for a file
src/CraftingBar.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/CraftingBar.cpp.s
.PHONY : src/CraftingBar.cpp.s

src/Enemy.o: src/Enemy.cpp.o
.PHONY : src/Enemy.o

# target to build an object file
src/Enemy.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Enemy.cpp.o
.PHONY : src/Enemy.cpp.o

src/Enemy.i: src/Enemy.cpp.i
.PHONY : src/Enemy.i

# target to preprocess a source file
src/Enemy.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Enemy.cpp.i
.PHONY : src/Enemy.cpp.i

src/Enemy.s: src/Enemy.cpp.s
.PHONY : src/Enemy.s

# target to generate assembly for a file
src/Enemy.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Enemy.cpp.s
.PHONY : src/Enemy.cpp.s

src/FlyingEnemy.o: src/FlyingEnemy.cpp.o
.PHONY : src/FlyingEnemy.o

# target to build an object file
src/FlyingEnemy.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/FlyingEnemy.cpp.o
.PHONY : src/FlyingEnemy.cpp.o

src/FlyingEnemy.i: src/FlyingEnemy.cpp.i
.PHONY : src/FlyingEnemy.i

# target to preprocess a source file
src/FlyingEnemy.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/FlyingEnemy.cpp.i
.PHONY : src/FlyingEnemy.cpp.i

src/FlyingEnemy.s: src/FlyingEnemy.cpp.s
.PHONY : src/FlyingEnemy.s

# target to generate assembly for a file
src/FlyingEnemy.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/FlyingEnemy.cpp.s
.PHONY : src/FlyingEnemy.cpp.s

src/Game.o: src/Game.cpp.o
.PHONY : src/Game.o

# target to build an object file
src/Game.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Game.cpp.o
.PHONY : src/Game.cpp.o

src/Game.i: src/Game.cpp.i
.PHONY : src/Game.i

# target to preprocess a source file
src/Game.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Game.cpp.i
.PHONY : src/Game.cpp.i

src/Game.s: src/Game.cpp.s
.PHONY : src/Game.s

# target to generate assembly for a file
src/Game.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Game.cpp.s
.PHONY : src/Game.cpp.s

src/GroundEnemy.o: src/GroundEnemy.cpp.o
.PHONY : src/GroundEnemy.o

# target to build an object file
src/GroundEnemy.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/GroundEnemy.cpp.o
.PHONY : src/GroundEnemy.cpp.o

src/GroundEnemy.i: src/GroundEnemy.cpp.i
.PHONY : src/GroundEnemy.i

# target to preprocess a source file
src/GroundEnemy.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/GroundEnemy.cpp.i
.PHONY : src/GroundEnemy.cpp.i

src/GroundEnemy.s: src/GroundEnemy.cpp.s
.PHONY : src/GroundEnemy.s

# target to generate assembly for a file
src/GroundEnemy.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/GroundEnemy.cpp.s
.PHONY : src/GroundEnemy.cpp.s

src/ISceneNode.o: src/ISceneNode.cpp.o
.PHONY : src/ISceneNode.o

# target to build an object file
src/ISceneNode.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/ISceneNode.cpp.o
.PHONY : src/ISceneNode.cpp.o

src/ISceneNode.i: src/ISceneNode.cpp.i
.PHONY : src/ISceneNode.i

# target to preprocess a source file
src/ISceneNode.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/ISceneNode.cpp.i
.PHONY : src/ISceneNode.cpp.i

src/ISceneNode.s: src/ISceneNode.cpp.s
.PHONY : src/ISceneNode.s

# target to generate assembly for a file
src/ISceneNode.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/ISceneNode.cpp.s
.PHONY : src/ISceneNode.cpp.s

src/Inventory.o: src/Inventory.cpp.o
.PHONY : src/Inventory.o

# target to build an object file
src/Inventory.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Inventory.cpp.o
.PHONY : src/Inventory.cpp.o

src/Inventory.i: src/Inventory.cpp.i
.PHONY : src/Inventory.i

# target to preprocess a source file
src/Inventory.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Inventory.cpp.i
.PHONY : src/Inventory.cpp.i

src/Inventory.s: src/Inventory.cpp.s
.PHONY : src/Inventory.s

# target to generate assembly for a file
src/Inventory.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Inventory.cpp.s
.PHONY : src/Inventory.cpp.s

src/Item.o: src/Item.cpp.o
.PHONY : src/Item.o

# target to build an object file
src/Item.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Item.cpp.o
.PHONY : src/Item.cpp.o

src/Item.i: src/Item.cpp.i
.PHONY : src/Item.i

# target to preprocess a source file
src/Item.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Item.cpp.i
.PHONY : src/Item.cpp.i

src/Item.s: src/Item.cpp.s
.PHONY : src/Item.s

# target to generate assembly for a file
src/Item.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Item.cpp.s
.PHONY : src/Item.cpp.s

src/ItemBomb.o: src/ItemBomb.cpp.o
.PHONY : src/ItemBomb.o

# target to build an object file
src/ItemBomb.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/ItemBomb.cpp.o
.PHONY : src/ItemBomb.cpp.o

src/ItemBomb.i: src/ItemBomb.cpp.i
.PHONY : src/ItemBomb.i

# target to preprocess a source file
src/ItemBomb.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/ItemBomb.cpp.i
.PHONY : src/ItemBomb.cpp.i

src/ItemBomb.s: src/ItemBomb.cpp.s
.PHONY : src/ItemBomb.s

# target to generate assembly for a file
src/ItemBomb.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/ItemBomb.cpp.s
.PHONY : src/ItemBomb.cpp.s

src/ItemPickaxe.o: src/ItemPickaxe.cpp.o
.PHONY : src/ItemPickaxe.o

# target to build an object file
src/ItemPickaxe.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/ItemPickaxe.cpp.o
.PHONY : src/ItemPickaxe.cpp.o

src/ItemPickaxe.i: src/ItemPickaxe.cpp.i
.PHONY : src/ItemPickaxe.i

# target to preprocess a source file
src/ItemPickaxe.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/ItemPickaxe.cpp.i
.PHONY : src/ItemPickaxe.cpp.i

src/ItemPickaxe.s: src/ItemPickaxe.cpp.s
.PHONY : src/ItemPickaxe.s

# target to generate assembly for a file
src/ItemPickaxe.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/ItemPickaxe.cpp.s
.PHONY : src/ItemPickaxe.cpp.s

src/ItemSword.o: src/ItemSword.cpp.o
.PHONY : src/ItemSword.o

# target to build an object file
src/ItemSword.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/ItemSword.cpp.o
.PHONY : src/ItemSword.cpp.o

src/ItemSword.i: src/ItemSword.cpp.i
.PHONY : src/ItemSword.i

# target to preprocess a source file
src/ItemSword.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/ItemSword.cpp.i
.PHONY : src/ItemSword.cpp.i

src/ItemSword.s: src/ItemSword.cpp.s
.PHONY : src/ItemSword.s

# target to generate assembly for a file
src/ItemSword.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/ItemSword.cpp.s
.PHONY : src/ItemSword.cpp.s

src/PerlinNoise.o: src/PerlinNoise.cpp.o
.PHONY : src/PerlinNoise.o

# target to build an object file
src/PerlinNoise.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/PerlinNoise.cpp.o
.PHONY : src/PerlinNoise.cpp.o

src/PerlinNoise.i: src/PerlinNoise.cpp.i
.PHONY : src/PerlinNoise.i

# target to preprocess a source file
src/PerlinNoise.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/PerlinNoise.cpp.i
.PHONY : src/PerlinNoise.cpp.i

src/PerlinNoise.s: src/PerlinNoise.cpp.s
.PHONY : src/PerlinNoise.s

# target to generate assembly for a file
src/PerlinNoise.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/PerlinNoise.cpp.s
.PHONY : src/PerlinNoise.cpp.s

src/Player.o: src/Player.cpp.o
.PHONY : src/Player.o

# target to build an object file
src/Player.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Player.cpp.o
.PHONY : src/Player.cpp.o

src/Player.i: src/Player.cpp.i
.PHONY : src/Player.i

# target to preprocess a source file
src/Player.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Player.cpp.i
.PHONY : src/Player.cpp.i

src/Player.s: src/Player.cpp.s
.PHONY : src/Player.s

# target to generate assembly for a file
src/Player.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Player.cpp.s
.PHONY : src/Player.cpp.s

src/Projectile.o: src/Projectile.cpp.o
.PHONY : src/Projectile.o

# target to build an object file
src/Projectile.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Projectile.cpp.o
.PHONY : src/Projectile.cpp.o

src/Projectile.i: src/Projectile.cpp.i
.PHONY : src/Projectile.i

# target to preprocess a source file
src/Projectile.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Projectile.cpp.i
.PHONY : src/Projectile.cpp.i

src/Projectile.s: src/Projectile.cpp.s
.PHONY : src/Projectile.s

# target to generate assembly for a file
src/Projectile.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Projectile.cpp.s
.PHONY : src/Projectile.cpp.s

src/Rect.o: src/Rect.cpp.o
.PHONY : src/Rect.o

# target to build an object file
src/Rect.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Rect.cpp.o
.PHONY : src/Rect.cpp.o

src/Rect.i: src/Rect.cpp.i
.PHONY : src/Rect.i

# target to preprocess a source file
src/Rect.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Rect.cpp.i
.PHONY : src/Rect.cpp.i

src/Rect.s: src/Rect.cpp.s
.PHONY : src/Rect.s

# target to generate assembly for a file
src/Rect.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Rect.cpp.s
.PHONY : src/Rect.cpp.s

src/Scene.o: src/Scene.cpp.o
.PHONY : src/Scene.o

# target to build an object file
src/Scene.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Scene.cpp.o
.PHONY : src/Scene.cpp.o

src/Scene.i: src/Scene.cpp.i
.PHONY : src/Scene.i

# target to preprocess a source file
src/Scene.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Scene.cpp.i
.PHONY : src/Scene.cpp.i

src/Scene.s: src/Scene.cpp.s
.PHONY : src/Scene.s

# target to generate assembly for a file
src/Scene.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Scene.cpp.s
.PHONY : src/Scene.cpp.s

src/SceneCredits.o: src/SceneCredits.cpp.o
.PHONY : src/SceneCredits.o

# target to build an object file
src/SceneCredits.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/SceneCredits.cpp.o
.PHONY : src/SceneCredits.cpp.o

src/SceneCredits.i: src/SceneCredits.cpp.i
.PHONY : src/SceneCredits.i

# target to preprocess a source file
src/SceneCredits.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/SceneCredits.cpp.i
.PHONY : src/SceneCredits.cpp.i

src/SceneCredits.s: src/SceneCredits.cpp.s
.PHONY : src/SceneCredits.s

# target to generate assembly for a file
src/SceneCredits.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/SceneCredits.cpp.s
.PHONY : src/SceneCredits.cpp.s

src/SceneGame.o: src/SceneGame.cpp.o
.PHONY : src/SceneGame.o

# target to build an object file
src/SceneGame.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/SceneGame.cpp.o
.PHONY : src/SceneGame.cpp.o

src/SceneGame.i: src/SceneGame.cpp.i
.PHONY : src/SceneGame.i

# target to preprocess a source file
src/SceneGame.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/SceneGame.cpp.i
.PHONY : src/SceneGame.cpp.i

src/SceneGame.s: src/SceneGame.cpp.s
.PHONY : src/SceneGame.s

# target to generate assembly for a file
src/SceneGame.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/SceneGame.cpp.s
.PHONY : src/SceneGame.cpp.s

src/SceneInstructions.o: src/SceneInstructions.cpp.o
.PHONY : src/SceneInstructions.o

# target to build an object file
src/SceneInstructions.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/SceneInstructions.cpp.o
.PHONY : src/SceneInstructions.cpp.o

src/SceneInstructions.i: src/SceneInstructions.cpp.i
.PHONY : src/SceneInstructions.i

# target to preprocess a source file
src/SceneInstructions.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/SceneInstructions.cpp.i
.PHONY : src/SceneInstructions.cpp.i

src/SceneInstructions.s: src/SceneInstructions.cpp.s
.PHONY : src/SceneInstructions.s

# target to generate assembly for a file
src/SceneInstructions.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/SceneInstructions.cpp.s
.PHONY : src/SceneInstructions.cpp.s

src/SceneMenu.o: src/SceneMenu.cpp.o
.PHONY : src/SceneMenu.o

# target to build an object file
src/SceneMenu.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/SceneMenu.cpp.o
.PHONY : src/SceneMenu.cpp.o

src/SceneMenu.i: src/SceneMenu.cpp.i
.PHONY : src/SceneMenu.i

# target to preprocess a source file
src/SceneMenu.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/SceneMenu.cpp.i
.PHONY : src/SceneMenu.cpp.i

src/SceneMenu.s: src/SceneMenu.cpp.s
.PHONY : src/SceneMenu.s

# target to generate assembly for a file
src/SceneMenu.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/SceneMenu.cpp.s
.PHONY : src/SceneMenu.cpp.s

src/Shader.o: src/Shader.cpp.o
.PHONY : src/Shader.o

# target to build an object file
src/Shader.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Shader.cpp.o
.PHONY : src/Shader.cpp.o

src/Shader.i: src/Shader.cpp.i
.PHONY : src/Shader.i

# target to preprocess a source file
src/Shader.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Shader.cpp.i
.PHONY : src/Shader.cpp.i

src/Shader.s: src/Shader.cpp.s
.PHONY : src/Shader.s

# target to generate assembly for a file
src/Shader.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Shader.cpp.s
.PHONY : src/Shader.cpp.s

src/ShaderProgram.o: src/ShaderProgram.cpp.o
.PHONY : src/ShaderProgram.o

# target to build an object file
src/ShaderProgram.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/ShaderProgram.cpp.o
.PHONY : src/ShaderProgram.cpp.o

src/ShaderProgram.i: src/ShaderProgram.cpp.i
.PHONY : src/ShaderProgram.i

# target to preprocess a source file
src/ShaderProgram.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/ShaderProgram.cpp.i
.PHONY : src/ShaderProgram.cpp.i

src/ShaderProgram.s: src/ShaderProgram.cpp.s
.PHONY : src/ShaderProgram.s

# target to generate assembly for a file
src/ShaderProgram.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/ShaderProgram.cpp.s
.PHONY : src/ShaderProgram.cpp.s

src/SoundManager.o: src/SoundManager.cpp.o
.PHONY : src/SoundManager.o

# target to build an object file
src/SoundManager.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/SoundManager.cpp.o
.PHONY : src/SoundManager.cpp.o

src/SoundManager.i: src/SoundManager.cpp.i
.PHONY : src/SoundManager.i

# target to preprocess a source file
src/SoundManager.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/SoundManager.cpp.i
.PHONY : src/SoundManager.cpp.i

src/SoundManager.s: src/SoundManager.cpp.s
.PHONY : src/SoundManager.s

# target to generate assembly for a file
src/SoundManager.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/SoundManager.cpp.s
.PHONY : src/SoundManager.cpp.s

src/Sprite.o: src/Sprite.cpp.o
.PHONY : src/Sprite.o

# target to build an object file
src/Sprite.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Sprite.cpp.o
.PHONY : src/Sprite.cpp.o

src/Sprite.i: src/Sprite.cpp.i
.PHONY : src/Sprite.i

# target to preprocess a source file
src/Sprite.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Sprite.cpp.i
.PHONY : src/Sprite.cpp.i

src/Sprite.s: src/Sprite.cpp.s
.PHONY : src/Sprite.s

# target to generate assembly for a file
src/Sprite.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Sprite.cpp.s
.PHONY : src/Sprite.cpp.s

src/TemporaryEffect.o: src/TemporaryEffect.cpp.o
.PHONY : src/TemporaryEffect.o

# target to build an object file
src/TemporaryEffect.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/TemporaryEffect.cpp.o
.PHONY : src/TemporaryEffect.cpp.o

src/TemporaryEffect.i: src/TemporaryEffect.cpp.i
.PHONY : src/TemporaryEffect.i

# target to preprocess a source file
src/TemporaryEffect.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/TemporaryEffect.cpp.i
.PHONY : src/TemporaryEffect.cpp.i

src/TemporaryEffect.s: src/TemporaryEffect.cpp.s
.PHONY : src/TemporaryEffect.s

# target to generate assembly for a file
src/TemporaryEffect.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/TemporaryEffect.cpp.s
.PHONY : src/TemporaryEffect.cpp.s

src/Text.o: src/Text.cpp.o
.PHONY : src/Text.o

# target to build an object file
src/Text.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Text.cpp.o
.PHONY : src/Text.cpp.o

src/Text.i: src/Text.cpp.i
.PHONY : src/Text.i

# target to preprocess a source file
src/Text.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Text.cpp.i
.PHONY : src/Text.cpp.i

src/Text.s: src/Text.cpp.s
.PHONY : src/Text.s

# target to generate assembly for a file
src/Text.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Text.cpp.s
.PHONY : src/Text.cpp.s

src/Texture.o: src/Texture.cpp.o
.PHONY : src/Texture.o

# target to build an object file
src/Texture.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Texture.cpp.o
.PHONY : src/Texture.cpp.o

src/Texture.i: src/Texture.cpp.i
.PHONY : src/Texture.i

# target to preprocess a source file
src/Texture.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Texture.cpp.i
.PHONY : src/Texture.cpp.i

src/Texture.s: src/Texture.cpp.s
.PHONY : src/Texture.s

# target to generate assembly for a file
src/Texture.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Texture.cpp.s
.PHONY : src/Texture.cpp.s

src/Tile.o: src/Tile.cpp.o
.PHONY : src/Tile.o

# target to build an object file
src/Tile.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Tile.cpp.o
.PHONY : src/Tile.cpp.o

src/Tile.i: src/Tile.cpp.i
.PHONY : src/Tile.i

# target to preprocess a source file
src/Tile.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Tile.cpp.i
.PHONY : src/Tile.cpp.i

src/Tile.s: src/Tile.cpp.s
.PHONY : src/Tile.s

# target to generate assembly for a file
src/Tile.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/Tile.cpp.s
.PHONY : src/Tile.cpp.s

src/TileMap.o: src/TileMap.cpp.o
.PHONY : src/TileMap.o

# target to build an object file
src/TileMap.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/TileMap.cpp.o
.PHONY : src/TileMap.cpp.o

src/TileMap.i: src/TileMap.cpp.i
.PHONY : src/TileMap.i

# target to preprocess a source file
src/TileMap.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/TileMap.cpp.i
.PHONY : src/TileMap.cpp.i

src/TileMap.s: src/TileMap.cpp.s
.PHONY : src/TileMap.s

# target to generate assembly for a file
src/TileMap.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/TileMap.cpp.s
.PHONY : src/TileMap.cpp.s

src/WinSymbol.o: src/WinSymbol.cpp.o
.PHONY : src/WinSymbol.o

# target to build an object file
src/WinSymbol.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/WinSymbol.cpp.o
.PHONY : src/WinSymbol.cpp.o

src/WinSymbol.i: src/WinSymbol.cpp.i
.PHONY : src/WinSymbol.i

# target to preprocess a source file
src/WinSymbol.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/WinSymbol.cpp.i
.PHONY : src/WinSymbol.cpp.i

src/WinSymbol.s: src/WinSymbol.cpp.s
.PHONY : src/WinSymbol.s

# target to generate assembly for a file
src/WinSymbol.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/WinSymbol.cpp.s
.PHONY : src/WinSymbol.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/Minaria.dir/build.make CMakeFiles/Minaria.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... Minaria"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... src/Background.o"
	@echo "... src/Background.i"
	@echo "... src/Background.s"
	@echo "... src/Block.o"
	@echo "... src/Block.i"
	@echo "... src/Block.s"
	@echo "... src/Bomb.o"
	@echo "... src/Bomb.i"
	@echo "... src/Bomb.s"
	@echo "... src/BombExplosion.o"
	@echo "... src/BombExplosion.i"
	@echo "... src/BombExplosion.s"
	@echo "... src/Camera.o"
	@echo "... src/Camera.i"
	@echo "... src/Camera.s"
	@echo "... src/Character.o"
	@echo "... src/Character.i"
	@echo "... src/Character.s"
	@echo "... src/CraftingBar.o"
	@echo "... src/CraftingBar.i"
	@echo "... src/CraftingBar.s"
	@echo "... src/Enemy.o"
	@echo "... src/Enemy.i"
	@echo "... src/Enemy.s"
	@echo "... src/FlyingEnemy.o"
	@echo "... src/FlyingEnemy.i"
	@echo "... src/FlyingEnemy.s"
	@echo "... src/Game.o"
	@echo "... src/Game.i"
	@echo "... src/Game.s"
	@echo "... src/GroundEnemy.o"
	@echo "... src/GroundEnemy.i"
	@echo "... src/GroundEnemy.s"
	@echo "... src/ISceneNode.o"
	@echo "... src/ISceneNode.i"
	@echo "... src/ISceneNode.s"
	@echo "... src/Inventory.o"
	@echo "... src/Inventory.i"
	@echo "... src/Inventory.s"
	@echo "... src/Item.o"
	@echo "... src/Item.i"
	@echo "... src/Item.s"
	@echo "... src/ItemBomb.o"
	@echo "... src/ItemBomb.i"
	@echo "... src/ItemBomb.s"
	@echo "... src/ItemPickaxe.o"
	@echo "... src/ItemPickaxe.i"
	@echo "... src/ItemPickaxe.s"
	@echo "... src/ItemSword.o"
	@echo "... src/ItemSword.i"
	@echo "... src/ItemSword.s"
	@echo "... src/PerlinNoise.o"
	@echo "... src/PerlinNoise.i"
	@echo "... src/PerlinNoise.s"
	@echo "... src/Player.o"
	@echo "... src/Player.i"
	@echo "... src/Player.s"
	@echo "... src/Projectile.o"
	@echo "... src/Projectile.i"
	@echo "... src/Projectile.s"
	@echo "... src/Rect.o"
	@echo "... src/Rect.i"
	@echo "... src/Rect.s"
	@echo "... src/Scene.o"
	@echo "... src/Scene.i"
	@echo "... src/Scene.s"
	@echo "... src/SceneCredits.o"
	@echo "... src/SceneCredits.i"
	@echo "... src/SceneCredits.s"
	@echo "... src/SceneGame.o"
	@echo "... src/SceneGame.i"
	@echo "... src/SceneGame.s"
	@echo "... src/SceneInstructions.o"
	@echo "... src/SceneInstructions.i"
	@echo "... src/SceneInstructions.s"
	@echo "... src/SceneMenu.o"
	@echo "... src/SceneMenu.i"
	@echo "... src/SceneMenu.s"
	@echo "... src/Shader.o"
	@echo "... src/Shader.i"
	@echo "... src/Shader.s"
	@echo "... src/ShaderProgram.o"
	@echo "... src/ShaderProgram.i"
	@echo "... src/ShaderProgram.s"
	@echo "... src/SoundManager.o"
	@echo "... src/SoundManager.i"
	@echo "... src/SoundManager.s"
	@echo "... src/Sprite.o"
	@echo "... src/Sprite.i"
	@echo "... src/Sprite.s"
	@echo "... src/TemporaryEffect.o"
	@echo "... src/TemporaryEffect.i"
	@echo "... src/TemporaryEffect.s"
	@echo "... src/Text.o"
	@echo "... src/Text.i"
	@echo "... src/Text.s"
	@echo "... src/Texture.o"
	@echo "... src/Texture.i"
	@echo "... src/Texture.s"
	@echo "... src/Tile.o"
	@echo "... src/Tile.i"
	@echo "... src/Tile.s"
	@echo "... src/TileMap.o"
	@echo "... src/TileMap.i"
	@echo "... src/TileMap.s"
	@echo "... src/WinSymbol.o"
	@echo "... src/WinSymbol.i"
	@echo "... src/WinSymbol.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

