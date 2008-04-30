CC=g++
CFLAGS=-c -w -g
LDFLAGS=-w -g ../../GUI.o ../../Window.o ../../Graph.o -lfltk -lXft -lfltk_images -ljpeg
SOURCES=Molinator_Window.h Molinator_Window.cpp Molinator.cpp Grid.h Grid.cpp Mole.h Mole.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=game

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o game

#Note: Visual C++ users may need to change the pointers in callbacks
