CC = g++

SOURCE = main.cpp chip8.cpp

INCLUDE_PATHS = -IC:\sdl\include\SDL2

LIBRARY_PATHS = -LC:\sdl\lib

COMPILER_FLAGS = -w -Wl,-subsystem,windows

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

OUTPUT = chip8

build : $(SOURCE)
	$(CC) $(SOURCE) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUTPUT)

debug : $(SOURCE)
	$(CC) $(SOURCE) $(INCLUDE_PATHS) -D DEBUG $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $(OUTPUT)