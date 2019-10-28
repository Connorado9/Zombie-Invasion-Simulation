// Connor Humiston
// Godley 310
// Data Structures
// Final Project: A Nation Divided

// This file contains main and the program

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "CityGraph2.hpp"
using namespace std;

int main(int argc, char* argv[])
{
	//instantiate the Graph and insert all the movies from the filename that was passed in the command line
	CityGraph graph;
	string adjacencyMatrixFileName = argv[1];
	graph.insertCities(adjacencyMatrixFileName);

	bool isRunning = true;
    while(isRunning)
    {
        //Program start
        //Printing the menu:
        cout << "\n";
        cout << "======Main Menu======" << endl;
        cout << "1. Print Vertices" << endl;
        //cout << "2. Vertex Adjacent" << endl;
        //cout << "3. Quit" << endl;
        cout << "2. Find Districts" << endl;
        cout << "3. Find Shortest Path" << endl;
        cout << "4. Find Shortest Weighted Path" << endl;
        cout << "5. Zombie Infection!" << endl;
        cout << "6. Quit" << endl;

        int numIn;
        cin >> numIn;

        switch(numIn)
        {
            case 1: //Print the vertices
            {
                cout << "Print Vertices" << endl;
                cout << "\n";

                graph.printVertices();

                break;
            }

            case 2: //Find the districts
            {
                cout << "Find Districts" << endl;
                //cout << "\n";

                graph.findDistricts();
                cout << "\nDistricts have been found and saved" << endl;
                break;
            }

            case 3: //Find the shortest path
            {
                cout << "Find Shortest Path" << endl;
                cout << "\n";

                string city1 = "";
                string city2 = "";

                cin.ignore();
                cout << "Enter a starting city: " << endl;
                getline(cin, city1);

                cout << "Enter an ending city: " << endl;
                getline(cin, city2);

                graph.findShortestPath(city1, city2);

                cout << "\n";
                break;
            }

            case 4: //Find the shortest weighted path
            {
                cout << "Find Shortest Weighted Path" << endl;
                cout << "\n";

                string city1 = "";
                string city2 = "";

                cin.ignore();
                cout << "Enter a starting city: " << endl;
				getline(cin, city1);

				cout << "Enter an ending city: " << endl;
				getline(cin, city2);

                graph.findShortestWeightedPath(city1, city2);

                cout << "\n";
                break;
            }

            case 5: //Zombie Infection!
            {
                cout << "Starting Infection!" << endl;
                cout << "\n";

                cout << "Timesteps for infection: " << graph.zombieInfection() << endl;

                break;
            }

            case 6: //Quit
            {
                cout << "Goodbye!\n" << endl;
                isRunning = false;
                graph.~CityGraph();
                exit(0);
                break;
            }
            
            /* 
            case 2: //Vertex Adjacent (pt. 1)
            {
                // This option takes two vertices as user inputs and displays 
                // True is the vertices are adjacent &
                // False if they are not adjacent

                cout << "Vertex Adjacent" << endl;
                cout << "\n";

                string city1 = "";
                string city2 = "";

                cin.ignore();
                cout << "Enter a starting city: " << endl;
                getline(cin, city1);

                cout << "Enter an ending city: " << endl;
                getline(cin, city2);

                if(graph.isAdjacent(city1, city2) == 1)
                    cout << "\nTrue" << endl;
                else
                    cout << "\nFalse" << endl;

                break;
            }
            */

            default:
            {
                cout << "Sorry that wasn't an option. Please reload the program and try again." << endl;
                isRunning = false;
            }
        }
    }
}