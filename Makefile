
all: clean  project

project: project.cpp
	g++ project.cpp -Wall -o project

clean: 
	rm -f project
