TARGET ?= linux

all: $(TARGET)

windows:
	g++ ../src/*.cpp -o Game.exe -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
linux:
  g++ ../src/*.cpp -o Game -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/ -lraylib -lm -lpthread -ldl -lrt -lX11

.PHONY: all windows linux
