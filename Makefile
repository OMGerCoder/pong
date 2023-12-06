TARGET ?= linux

all: $(TARGET)

windows:
	mkdir -p build
	g++ ./src/*.cpp -o ./build/Game.exe -O2 -Wall -Wno-missing-braces -I ./include/ -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

linux:
	mkdir -p build
	g++ ./src/*.cpp -o ./build/Game -O2 -Wall -Wno-missing-braces -I ./include/ -L ./lib/ -lraylib -lm -lpthread -ldl -lrt -lX11

.PHONY: all windows linux
