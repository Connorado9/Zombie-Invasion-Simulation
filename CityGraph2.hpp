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

    //Linked List info
    AdjacentCity* next;     // pointer to the next city
    AdjacentCity* prev;     // pointer to the previous city
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

    bool visited;           // for searches
    bool infected;          // whether the city is infected at the start or not
    bool tempinfection;     // for current iteration of simulation
    bool infection;         // for after the simulation
    int ID;                 // the district ID for a vertex city
    int pathDistance;       // this stores the total distance from the starting city when traversing a path
    CityVertex* parent;     // for Dikstra's
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

struct Node
{
    CityVertex* vertex;
    Node* next;
    Node* prev;
};

// Queue class for graph search algorithms
class Queue 
{
private:
    Node* head;

    // Returns the tail of the linked list for the append function
    Node* gettail();
public:
    // Constructor
    Queue();
    //Destructor
    ~Queue();

    // Adds a vertex to the tail of the queue (last in last out)
    void enqueue(CityVertex* v);
    
    // Removes from the head of the queue (first in first out)
    CityVertex* dequeue();

    // Returns true if the queue is empty and false otherwise
    bool isEmpty();
};

struct StackNode
{
    string key;
    StackNode* next;
    StackNode* prev;
};

// Stack class of strings to print the search paths backwards
class Stack
{
private:
    StackNode* head;
    StackNode* tail;
public:
    // Constructor
    Stack();
    
    // Adds a vertex to the stack
    void push(string name);

    // Pops and returns a vertex from the stack
    string pop();

    // Prints the stack from top to bottom
    void printTopToBottom();
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

        // Taking in two vertices, this method checks to see if they are adjacent
        bool isAdjacent(string v1, string v2);

        // findDistricts performs a depth-first search to determine connected cities, and assign those cities a district ID
        // Districts are cities either connected directly by an edge or indirectly by another vertex
        // A district ID from 1 to n is maintianed for each vertex
        void findDistricts();

        // performs a depth-first search for the find districts function
        void DFS_helper(CityVertex* vertex, int district);

        // When this options is selected, the user is promted for the names of two cities
        // If the cities are in the different districts, "No safe path between cities"
        // If the cities are in the same district, a breadth-first search is executed
        // And the number and name of edges along the shortes path are returned
        void findShortestPath(string city1, string city2);

        // This option prompts for the names of two cities and determines if they are in the same district
        // If the cities are in different districts, “No safe path between cities” is printed
        // If the cities are in the same district, Dijkstra’s algorithm finds the shortest distance between the cities
        // Both the distance and the names of vertices along the path are printed
        void findShortestWeightedPath(string city1, string city2);

        // The adjacency matrix contains an infection parameter that acts as an indicator variable to determine whether a city has been infected
        // When the user selects this option, an infection process begins at t=0
        // For the first time step, any existing cities that are infected will begin infecting their adjacent neighbors
        // In a single time step, a city may only be infected if one of its neighbors was already infected at the start of that time step
        // The number of time steps the graph took to allow the zombie infection to run its course is output
        int zombieInfection();

        // Infects adjacent cities given a vertex, and returns true if there was a city left to infect
        bool infectNeighbors(CityVertex* vert);

        // Prints the vertices and adjacent vertices
        void printVertices();        
};



