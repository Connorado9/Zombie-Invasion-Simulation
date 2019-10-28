// Connor Humiston
// Godley 310
// Data Structures
// Final Project: A Nation Divided

// This is the class prototype/header file with struct, class, and method definitions

#pragma once //we are including this file in the .cpp and assignment.cpp just once
#include <iostream>
using namespace std;

// Vertex struct for Graph
struct CityVertex;

// Adjacent city in CityVertex list
struct AdjacentCity
{
    CityVertex* vertex;     // pointer to the vertex city 
    int distance;           // distance from the vertex city
    bool solved;            // for searches
    CityVertex* parent;     // for Dikstra's

    //Linked List info
    AdjacentCity* next;           // pointer to the next city
    AdjacentCity* prev;           // pointer to the previous city
};

// Linked List class for manipulating adjacent city nodes
class LinkedList
{
private:
    AdjacentCity* head;

    // The helper function for append that returns the tail
    AdjacentCity* gettail();

public:
    //constructor
    LinkedList();
    //destructor
    ~LinkedList();

    // Insert a new city into the linked list after the previousCityName
    //void addCity(string newCityName, string previousCityName);

    // Appends a new adjacent city to the end of the linked list given its vertex pointer and distance
    void append(CityVertex* city, int d);

    // Start at the head and print the name of each city in order to the end of the list
    void traverse();

    // Returns the head to point to from the array of vertices
    AdjacentCity* gethead();
    
    // Returns the node with the matching cityname
    AdjacentCity* listSearch(string cityname);

    // Find the city in the network where city name matches removeCity
    // Change the next and previous pointers for the surrounding cities and frees the memory
    void deleteCity(string removeCity);

    // Delete all cities in the adjacent list, starting at the head city
    void deleteAdjacentList();
};

struct CityVertex
{
    string name;            // the name of the vertex city
    LinkedList* ll;         // pointer to a linked list of adjacent cities
};

// Array class to store vertices
class Array
{
private:
    CityVertex* array;      // pointer to an array of city vertices
    int length;             // array size
    int numElements;        // number of elements in the array
public:
    //constructor
    Array(int l);

    //destructor
    ~Array();

    // Array function for inserting a city vertex at an index
    void arrayInsert(int index, CityVertex* v);

    // Array method that returns the value at an input index
    CityVertex* get(int index);

    // Prints the elements of the array
    void printArray();

    // Doubles the size of the dynamic array
    void doubleArray();

    // Searches the array for a city name and returns the vertex
    CityVertex* arraySearch(string cityname);
};

// Graph class for storing and manipulating a graph of cities
class CityGraph // a list of edges and a list of cities
{
    private:
        Array* vertices;
    public:
        //constructor
        CityGraph();
        //destructor
        ~CityGraph();

        // Upon program start, the user will pass the name of the text file containing all city graph information
        // The file contains the names of the cities and the distances between them stored as an adjacency matrix
        // The insertCities method opens the file and reads all thee data to build the graph
        void insertCities(string fileName);

        // Adds cityVertex to the linked list
        void insertVertex(CityVertex city);

        // Taking in two vertices, this method checks to see if they are adjacent
        bool isAdjacent(string v1, string v2);

        // Deletes the cityVertex with the removeCityName
        void deleteVertex(string removeCityName);

        // Inserts an edge between the firstCity and secondCity, along with assigning a distance
        void insertEdge(string firstCity, string secondCity, int distance);

        // Deletes the edge connecting the firstCity and secondCity inputs
        void deleteEdge(string firstCity, string secondCity);

        // Prints the vertices and adjacent vertices
        void printVertices();

        // Returns a CityVertex with the passed cityName
        CityVertex* searchGraph(string cityName);
};
