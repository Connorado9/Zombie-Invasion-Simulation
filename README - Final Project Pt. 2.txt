Final Project: A Nation Divided Pt. 2
By Connor Humiston
7/26/19
Data Structures

Files: 
"CityGraph2.hpp" 	(struct, class, and method definitions)
"CityGraph2.cpp" 	(implementations)
"FinalProject2.cpp" 	(main method)

Purpose: The purpose of this program is to simulate a network of zombie infested cities using a graph. 

Description: This C++ program built in Sublime and run through the command line is passed a file with the names, distances, and infection state of cities in an adjacency matrix. Cities that have roads still connecting them (not cut off by zombies) have a positive distance, and cut off cities have a distance of -1. Cities that are safe are labeled with an S, and cities that are infected are labeled with an I. After running the program, a graph composed of a linked list of vertex city names pointing to arrays of adjacent cities is built from the file. After all the cities have been added to the graph, a main menu will be displayed with a list of options. Typing a 1 and then pressing enter will print the vertices. 2 will set the districts based on the cities that are connected to each other. 3 will find the shortest unweighted path between cities. 4 will find the shortest distance between two cities. 5 will simulate a zombie infection starting at infected cities, and outputting the number of time cycles taken to play out. Lastly, 6 will quit the program.


Running: The program can be compiled by typing g++ -std=c++11 followed by the file with the implementations in it followed by the main method file and then saved with -o
	For example:
		g++ -std=c++11 CityGraph2.cpp FinalProject2.cpp -o FinalProject2
	
Next, the program would be run by typing ./FinalProject followed by the name of the file with all the cities in it (as specified above).
	For example:
		./FinalProject2 zombieCitiesInfection.txt

