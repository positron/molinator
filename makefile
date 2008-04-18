CC=g++
CFLAGS=-c
LDFLAGS=../../GUI.o ../../Window.o ../../Graph.o -lfltk -lXft -lfltk_images
SOURCES=Handler.h Handler.cpp Molinator_Window.h Start_Handler.h Start_Handler.cpp Molinator.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=game

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o game

#all: game

#game: $(OBJECTS)
#  g++ $(OBJECTS) $(FLAGS) -o game

#Molinator_Window.o: Molinator_Window.cpp
#  g++ -c Molinator_Window.cpp 

#Timer.o: Timer.cpp
#  g++ -c Timer.cpp

#Scores.o: Scores.cpp
#  g++ -c Scores.cpp

#Mole.o: Mole.cpp
#  g++ -c Mole.cpp
