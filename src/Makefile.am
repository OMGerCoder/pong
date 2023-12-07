bin_PROGRAMS = Game
Game_SOURCES = src/main.cpp

# Additional source files if any
# Game_SOURCES += src/another_file.cpp

Game_CPPFLAGS = -I$(top_srcdir)/include
if WINDOWS
Game_LDADD = -L$(top_srcdir)/lib -lraylib -lopengl32 -lgdi32 -lwinmm
else
Game_LDADD = -L$(top_srcdir)/lib -lraylib -lm -lpthread -ldl -lrt -lX11
endif