
all: clean  project

project: project.cpp
	g++ project.cpp -Wall -o run

clean: 
	rm -f run
