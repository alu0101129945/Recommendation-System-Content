# Variables
TIME =$(LOGPATH)$(shell date)
# Object Vars
OBJECTS = main.o Recomendation.o Token.o Preprocessor.o Article.o
# Compilation flags
CFLAGS = -c -std=c++17 -Wall

recomendation: $(OBJECTS)
	g++ $(OBJECTS) -o recomendation
	mv recomendation ../bin

main.o: ../src/main.cpp
	g++ $(CFLAGS) ../src/main.cpp

Recomendation.o: ../src/Recomendation.cpp ../include/Recomendation.hpp
	g++ $(CFLAGS) ../src/Recomendation.cpp

Token.o: ../src/Token.cpp ../include/Token.hpp
	g++ $(CFLAGS) ../src/Token.cpp

Preprocessor.o: ../src/Preprocessor.cpp ../include/Preprocessor.hpp
	g++ $(CFLAGS) ../src/Preprocessor.cpp

Article.o: ../src/Article.cpp ../include/Article.hpp
	g++ $(CFLAGS) ../src/Article.cpp


.PHONY: clean
clean:
	rm -rf ../build/*.o
	rm -rf ../bin/*

run:
	../bin/recomendation ../inputs/input_file.txt