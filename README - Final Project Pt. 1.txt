Final Project: A Nation Divided Pt. 1
By Connor Humiston
7/18/19
Data Structures

Files: 
"CityGraph.hpp" 	(struct, class, and method definitions)
"CityGraph.cpp" 	(implementations)
"FinalProject.cpp" 	(main method)

Purpose: The purpose of this program is to simulate a network of cities among zombies using a graph. 

Description: This C++ program built in Sublime and run through the command line is passed a file with the names and distances of cities in an adjacency matrix. Cities that have roads still connecting them (not cut off by zombies) have a positive distance, and cut off cities have a distance of -1. After running the program, a graph composed of a linked list of vertex city names pointing to arrays of adjacent cities is built from the file. After all the cities have been added to the graph, a main menu will be displayed with a list of options. Typing a 1 and then pressing enter will print the vertices. 2 will ask for two vertices to verify if they are adjacent (connected) or not. Lastly, 3 will quit the program.


Running: The program can be compiled by typing g++ -std=c++11 followed by the file with the implementations in it followed by the main method file and then saved with -o
	For example:
		g++ -std=c++11 CityGraph.cpp FinalProject.cpp -o FinalProject
	
Next, the program would be run by typing ./FinalProject followed by the name of the file with all the cities in it (as specified above).
	For example:
		./FinalProject zombieCities.txt

