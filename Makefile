ENGINE_SRC = slam/*.cpp slam/*/*.cpp slam/ext/*/*.c


default:
	@echo $(ENGINE_SRC)
	g++ src/main.cpp $(ENGINE_SRC) -lSDL3 -o game