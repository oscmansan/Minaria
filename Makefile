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
CMAKE_SOURCE_DIR = /home/sephirot47/Terraria-linux

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sephirot47/Terraria-linux

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
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sephirot47/Terraria-linux/CMakeFiles /home/sephirot47/Terraria-linux/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sephirot47/Terraria-linux/CMakeFiles 0
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
# Target rules for targets named TerrariaLinux

# Build rule for target.
TerrariaLinux: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 TerrariaLinux
.PHONY : TerrariaLinux

# fast build rule for target.
TerrariaLinux/fast:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/build
.PHONY : TerrariaLinux/fast

Block.o: Block.cpp.o
.PHONY : Block.o

# target to build an object file
Block.cpp.o:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Block.cpp.o
.PHONY : Block.cpp.o

Block.i: Block.cpp.i
.PHONY : Block.i

# target to preprocess a source file
Block.cpp.i:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Block.cpp.i
.PHONY : Block.cpp.i

Block.s: Block.cpp.s
.PHONY : Block.s

# target to generate assembly for a file
Block.cpp.s:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Block.cpp.s
.PHONY : Block.cpp.s

Camera.o: Camera.cpp.o
.PHONY : Camera.o

# target to build an object file
Camera.cpp.o:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Camera.cpp.o
.PHONY : Camera.cpp.o

Camera.i: Camera.cpp.i
.PHONY : Camera.i

# target to preprocess a source file
Camera.cpp.i:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Camera.cpp.i
.PHONY : Camera.cpp.i

Camera.s: Camera.cpp.s
.PHONY : Camera.s

# target to generate assembly for a file
Camera.cpp.s:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Camera.cpp.s
.PHONY : Camera.cpp.s

Character.o: Character.cpp.o
.PHONY : Character.o

# target to build an object file
Character.cpp.o:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Character.cpp.o
.PHONY : Character.cpp.o

Character.i: Character.cpp.i
.PHONY : Character.i

# target to preprocess a source file
Character.cpp.i:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Character.cpp.i
.PHONY : Character.cpp.i

Character.s: Character.cpp.s
.PHONY : Character.s

# target to generate assembly for a file
Character.cpp.s:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Character.cpp.s
.PHONY : Character.cpp.s

Enemy.o: Enemy.cpp.o
.PHONY : Enemy.o

# target to build an object file
Enemy.cpp.o:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Enemy.cpp.o
.PHONY : Enemy.cpp.o

Enemy.i: Enemy.cpp.i
.PHONY : Enemy.i

# target to preprocess a source file
Enemy.cpp.i:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Enemy.cpp.i
.PHONY : Enemy.cpp.i

Enemy.s: Enemy.cpp.s
.PHONY : Enemy.s

# target to generate assembly for a file
Enemy.cpp.s:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Enemy.cpp.s
.PHONY : Enemy.cpp.s

Game.o: Game.cpp.o
.PHONY : Game.o

# target to build an object file
Game.cpp.o:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Game.cpp.o
.PHONY : Game.cpp.o

Game.i: Game.cpp.i
.PHONY : Game.i

# target to preprocess a source file
Game.cpp.i:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Game.cpp.i
.PHONY : Game.cpp.i

Game.s: Game.cpp.s
.PHONY : Game.s

# target to generate assembly for a file
Game.cpp.s:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Game.cpp.s
.PHONY : Game.cpp.s

Inventory.o: Inventory.cpp.o
.PHONY : Inventory.o

# target to build an object file
Inventory.cpp.o:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Inventory.cpp.o
.PHONY : Inventory.cpp.o

Inventory.i: Inventory.cpp.i
.PHONY : Inventory.i

# target to preprocess a source file
Inventory.cpp.i:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Inventory.cpp.i
.PHONY : Inventory.cpp.i

Inventory.s: Inventory.cpp.s
.PHONY : Inventory.s

# target to generate assembly for a file
Inventory.cpp.s:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Inventory.cpp.s
.PHONY : Inventory.cpp.s

Item.o: Item.cpp.o
.PHONY : Item.o

# target to build an object file
Item.cpp.o:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Item.cpp.o
.PHONY : Item.cpp.o

Item.i: Item.cpp.i
.PHONY : Item.i

# target to preprocess a source file
Item.cpp.i:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Item.cpp.i
.PHONY : Item.cpp.i

Item.s: Item.cpp.s
.PHONY : Item.s

# target to generate assembly for a file
Item.cpp.s:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Item.cpp.s
.PHONY : Item.cpp.s

PerlinNoise.o: PerlinNoise.cpp.o
.PHONY : PerlinNoise.o

# target to build an object file
PerlinNoise.cpp.o:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/PerlinNoise.cpp.o
.PHONY : PerlinNoise.cpp.o

PerlinNoise.i: PerlinNoise.cpp.i
.PHONY : PerlinNoise.i

# target to preprocess a source file
PerlinNoise.cpp.i:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/PerlinNoise.cpp.i
.PHONY : PerlinNoise.cpp.i

PerlinNoise.s: PerlinNoise.cpp.s
.PHONY : PerlinNoise.s

# target to generate assembly for a file
PerlinNoise.cpp.s:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/PerlinNoise.cpp.s
.PHONY : PerlinNoise.cpp.s

Player.o: Player.cpp.o
.PHONY : Player.o

# target to build an object file
Player.cpp.o:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Player.cpp.o
.PHONY : Player.cpp.o

Player.i: Player.cpp.i
.PHONY : Player.i

# target to preprocess a source file
Player.cpp.i:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Player.cpp.i
.PHONY : Player.cpp.i

Player.s: Player.cpp.s
.PHONY : Player.s

# target to generate assembly for a file
Player.cpp.s:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Player.cpp.s
.PHONY : Player.cpp.s

Rect.o: Rect.cpp.o
.PHONY : Rect.o

# target to build an object file
Rect.cpp.o:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Rect.cpp.o
.PHONY : Rect.cpp.o

Rect.i: Rect.cpp.i
.PHONY : Rect.i

# target to preprocess a source file
Rect.cpp.i:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Rect.cpp.i
.PHONY : Rect.cpp.i

Rect.s: Rect.cpp.s
.PHONY : Rect.s

# target to generate assembly for a file
Rect.cpp.s:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Rect.cpp.s
.PHONY : Rect.cpp.s

Scene.o: Scene.cpp.o
.PHONY : Scene.o

# target to build an object file
Scene.cpp.o:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Scene.cpp.o
.PHONY : Scene.cpp.o

Scene.i: Scene.cpp.i
.PHONY : Scene.i

# target to preprocess a source file
Scene.cpp.i:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Scene.cpp.i
.PHONY : Scene.cpp.i

Scene.s: Scene.cpp.s
.PHONY : Scene.s

# target to generate assembly for a file
Scene.cpp.s:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Scene.cpp.s
.PHONY : Scene.cpp.s

Shader.o: Shader.cpp.o
.PHONY : Shader.o

# target to build an object file
Shader.cpp.o:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Shader.cpp.o
.PHONY : Shader.cpp.o

Shader.i: Shader.cpp.i
.PHONY : Shader.i

# target to preprocess a source file
Shader.cpp.i:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Shader.cpp.i
.PHONY : Shader.cpp.i

Shader.s: Shader.cpp.s
.PHONY : Shader.s

# target to generate assembly for a file
Shader.cpp.s:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Shader.cpp.s
.PHONY : Shader.cpp.s

ShaderProgram.o: ShaderProgram.cpp.o
.PHONY : ShaderProgram.o

# target to build an object file
ShaderProgram.cpp.o:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/ShaderProgram.cpp.o
.PHONY : ShaderProgram.cpp.o

ShaderProgram.i: ShaderProgram.cpp.i
.PHONY : ShaderProgram.i

# target to preprocess a source file
ShaderProgram.cpp.i:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/ShaderProgram.cpp.i
.PHONY : ShaderProgram.cpp.i

ShaderProgram.s: ShaderProgram.cpp.s
.PHONY : ShaderProgram.s

# target to generate assembly for a file
ShaderProgram.cpp.s:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/ShaderProgram.cpp.s
.PHONY : ShaderProgram.cpp.s

Sprite.o: Sprite.cpp.o
.PHONY : Sprite.o

# target to build an object file
Sprite.cpp.o:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Sprite.cpp.o
.PHONY : Sprite.cpp.o

Sprite.i: Sprite.cpp.i
.PHONY : Sprite.i

# target to preprocess a source file
Sprite.cpp.i:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Sprite.cpp.i
.PHONY : Sprite.cpp.i

Sprite.s: Sprite.cpp.s
.PHONY : Sprite.s

# target to generate assembly for a file
Sprite.cpp.s:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Sprite.cpp.s
.PHONY : Sprite.cpp.s

Texture.o: Texture.cpp.o
.PHONY : Texture.o

# target to build an object file
Texture.cpp.o:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Texture.cpp.o
.PHONY : Texture.cpp.o

Texture.i: Texture.cpp.i
.PHONY : Texture.i

# target to preprocess a source file
Texture.cpp.i:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Texture.cpp.i
.PHONY : Texture.cpp.i

Texture.s: Texture.cpp.s
.PHONY : Texture.s

# target to generate assembly for a file
Texture.cpp.s:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/Texture.cpp.s
.PHONY : Texture.cpp.s

TileMap.o: TileMap.cpp.o
.PHONY : TileMap.o

# target to build an object file
TileMap.cpp.o:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/TileMap.cpp.o
.PHONY : TileMap.cpp.o

TileMap.i: TileMap.cpp.i
.PHONY : TileMap.i

# target to preprocess a source file
TileMap.cpp.i:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/TileMap.cpp.i
.PHONY : TileMap.cpp.i

TileMap.s: TileMap.cpp.s
.PHONY : TileMap.s

# target to generate assembly for a file
TileMap.cpp.s:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/TileMap.cpp.s
.PHONY : TileMap.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/TerrariaLinux.dir/build.make CMakeFiles/TerrariaLinux.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... TerrariaLinux"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Block.o"
	@echo "... Block.i"
	@echo "... Block.s"
	@echo "... Camera.o"
	@echo "... Camera.i"
	@echo "... Camera.s"
	@echo "... Character.o"
	@echo "... Character.i"
	@echo "... Character.s"
	@echo "... Enemy.o"
	@echo "... Enemy.i"
	@echo "... Enemy.s"
	@echo "... Game.o"
	@echo "... Game.i"
	@echo "... Game.s"
	@echo "... Inventory.o"
	@echo "... Inventory.i"
	@echo "... Inventory.s"
	@echo "... Item.o"
	@echo "... Item.i"
	@echo "... Item.s"
	@echo "... PerlinNoise.o"
	@echo "... PerlinNoise.i"
	@echo "... PerlinNoise.s"
	@echo "... Player.o"
	@echo "... Player.i"
	@echo "... Player.s"
	@echo "... Rect.o"
	@echo "... Rect.i"
	@echo "... Rect.s"
	@echo "... Scene.o"
	@echo "... Scene.i"
	@echo "... Scene.s"
	@echo "... Shader.o"
	@echo "... Shader.i"
	@echo "... Shader.s"
	@echo "... ShaderProgram.o"
	@echo "... ShaderProgram.i"
	@echo "... ShaderProgram.s"
	@echo "... Sprite.o"
	@echo "... Sprite.i"
	@echo "... Sprite.s"
	@echo "... Texture.o"
	@echo "... Texture.i"
	@echo "... Texture.s"
	@echo "... TileMap.o"
	@echo "... TileMap.i"
	@echo "... TileMap.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

