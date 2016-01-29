OBJ = main.o board.o
EXEC = converter
TAGS = g++ -Wall -g

$(EXEC): $(OBJ)
	$(TAGS) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(TAGS) -c $<

clean:
	rm -f $(OBJ) $(EXEC)