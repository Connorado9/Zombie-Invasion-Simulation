// Connor Humiston
// Godley 310
// Data Structures
// Final Project: A Nation Divided

// This file is where the following classes their methods are implemented
//   - Linked List Class
//   - Array Class
//	 - Queue Class
//   - Stack Class
//   - Graph class

#include "CityGraph2.hpp" //including the the other declarations
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//global variable for the number of cities in the graph
int citycount = 0;

/*===============================START OF LINKED LIST CLASS================================*/
//constructor
LinkedList::LinkedList()
{
	head = NULL;
}

//destructor
LinkedList::~LinkedList()
{
	deleteAdjacentList();
}

// The helper function for append that returns the tail
AdjacentCity* LinkedList::gethead()
{
	return head;
}

// The helper function for append that returns the tail
// If there is only once node in the list, beforecurr is still NULL
AdjacentCity* LinkedList::gettail()
{
	AdjacentCity* curr;
	AdjacentCity* beforecurr = NULL;
	curr = head;
	while (curr) 
	{
		beforecurr = curr;
		curr = curr->next;
	}
	return beforecurr;
}

// Appends a new adjacent city to the end of the linked list given a pointer to the city's vertex
void LinkedList::append(CityVertex* city, int d)
{
	AdjacentCity* newnode = new AdjacentCity;
	newnode->vertex = city;
	newnode->distance = d;
	newnode->next = NULL;
	newnode->prev = NULL;

	AdjacentCity* tail = gettail();
	if(tail != NULL)
	{
		tail->next = newnode;
	}
	else
	{
		head = newnode;
	}
}

// Start at the head and print the name of each city in order to the end of the list
void LinkedList::traverse()
{
	AdjacentCity *tmp = head;
	while(tmp != NULL)
	{
		cout << tmp->vertex->name;
		if(tmp->next != NULL) 
			cout << ", ";
		tmp = tmp->next;
	}
}

// Returns the node with the matching cityname
AdjacentCity* LinkedList::listSearch(string cityname)
{
    AdjacentCity* tmp = head; //temp starts at head
    while(tmp != NULL)
    {
        if(tmp->vertex->name == cityname)
            return tmp;
        tmp = tmp->next; //moving through the linked list if the temp node does not have the desired value
    }
    return NULL;
}

// Find the city in the network where city name matches removeCity
// Change the next and previous pointers for the surrounding cities and frees the memory
void LinkedList::deleteCity(string removeCity)
{
	AdjacentCity* cityDelete;
	AdjacentCity* temp = head; 
	AdjacentCity* toDelete;
	if(temp == NULL) //if head is NULL (nothing in the list)
	{
		cout << removeCity << " not found" << endl;
	}
	else if(head->vertex->name.compare(removeCity) == 0) //we are trying to delete the head
	{
		toDelete = head;
		cout << "deleting " << toDelete->vertex->name << endl;
		if(head->next != NULL)
			head->next->prev = NULL;
		head = head->next; 
		delete toDelete;
	}
	else //not deleting at the head
	{
		while(temp != NULL)
		{
			if(temp->next == NULL) //if the next is NULL (end of the list)
			{
				cout << removeCity << " not found" << endl;
				break;
			}
			else if(temp->next->vertex->name.compare(removeCity) == 0) //if the next node has the value we are looking for, temp is leftnode and next is toDelete
			{
				toDelete = temp->next; 
				if(toDelete->next == NULL) //if we are at tail
				{
					temp->next = NULL;
					cout << "deleting " << toDelete->vertex->name << endl;
					delete toDelete;
					break;
				}
				else //if we are not at tail
				{
					temp->next = toDelete->next;
					toDelete->next->prev = temp;
					cout << "deleting " << toDelete->vertex->name << endl;
					delete toDelete;
					break;
				}
			}
			temp = temp->next; //keeps going along the list
		}
	}
}

// Delete all cities in the network, starting at the head city
void LinkedList::deleteAdjacentList()
{
	AdjacentCity* temp = head; 
	while(temp != NULL)
	{
		if(temp->next != NULL)
		{
			deleteCity(temp->vertex->name);
			temp = temp->next;
		}
		else //if you are at the end of the list we only delete the last element, not move on
		{
			deleteCity(temp->vertex->name);
			break;
		}
	}
}
/*================================END OF LINKED LIST CLASS=================================*/



/*==================================START OF ARRAY CLASS===================================*/
//constructor
Array::Array(int l) 
{
    //instantiation
    array = new CityVertex[l];
    length = l;
    numElements = 0;
}

//destructor
Array::~Array() 
{
    delete array;
}

// Array function for inserting a city vertex at an index
void Array::arrayInsert(int index, CityVertex* v) 
{
    if(index < 0 || index > numElements)
    {
        cout << "ERROR: index out of bounds." << endl;
    }
    else
    {
        //cout << "Inserting: " << v->name << " at index " << index << endl;
        if(index >= length) 
        {
            //cout << "\nattempting to double array1" << endl;
            doubleArray();
        }
        for(int i = numElements-1; i >= index; i--) //moving data
        {
            if(i+1 < length) // Still have space to move data
            { 
                //cout << "\tReplacing A[" << i << "+1] = " << array[i+1].name << " with x[" << i << "]=" << array[i].name << endl;
                array[i+1] = array[i];
            } 
            else // Ran out of space while moving data
            {
                doubleArray();
                i++;
            }
        }
        array[index] = *v;
        //cout << "Replaced A[" << index << "] with: " << array[index].name << endl;
        numElements++;
    }
}

// Array method that returns the value at an input index
CityVertex* Array::get(int index)
{
    if (index >= 0 && index < length)
        return &array[index];
    else
    {
        cout << "ERROR: Index out of bounds." << endl;
        exit(1);
    }
}

// Prints the elements of the array - for testing purposes
void Array::printArray() 
{
    cout << "A[" << numElements << "] = [";
    for (int i=0; i<numElements; i++) 
    {
        cout << array[i].name;
        if (i < numElements-1) 
            cout << ", ";
    } 
    cout << "]" << endl;
}

// Doubles the size of the dynamic array
void Array::doubleArray()
{
    //instantiating the new array
    CityVertex* newarray = new CityVertex[length*2];

    //copying old data into the new array
    for(int i = 0; i < length; i++)
    {
        newarray[i] = array[i];
    }

    //updating private data members
    delete[] array;
    array = newarray;
    length = length * 2;
}

// Searches the array for a value and returns the index of that value
CityVertex* Array::arraySearch(string cityname) 
{ 
    bool found = false;
    int index = -1;
    int i = 0;
    while(!found && i < numElements) 
    {
        if(cityname.compare(array[i].name) == 0) 
        {
            found = true;
            index = i;
            break;
        }
        else
        {
            i++;
        }
    }
    if(index == -1)
    	return NULL;
    else
    	return &array[index];
}
/*===================================END OF ARRAY CLASS====================================*/



/*==================================START OF QUEUE CLASS===================================*/
// Constructor for linked list queue
Queue::Queue() 
{
    head = NULL;
}
//Destructor
Queue::~Queue(){}

// Returns the tail of the linked list for the append function
Node* Queue::gettail()
{
	Node* curr;
	Node* beforecurr = NULL;
	curr = head;
	while (curr) 
	{
		beforecurr = curr;
		curr = curr->next;
	}
	return beforecurr;
}

// Adds a vertex to the tail of the queue (last in last out)
void Queue::enqueue(CityVertex* v) 
{
   	Node* newNode = new Node;
	newNode->vertex = v;
	newNode->next = NULL;
	Node* tail = gettail();
	if (tail != NULL)
		tail->next = newNode;
	else
		head = newNode;
}

// Removes from the head of the queue (first in first out)
CityVertex* Queue::dequeue()
{
	//always deleting at the head
	Node* toDelete; 
	toDelete = head;
	if(toDelete == NULL)
	{
		return NULL;
	}
	else
	{
		head = head->next;
		return toDelete->vertex;
	}

}

// Returns true if the queue is empty and false otherwise
bool Queue::isEmpty()
{
	if(head == NULL)
		return true;
	return false;
}
/*===================================END OF QUEUE CLASS====================================*/


/*==================================START OF STACK CLASS===================================*/
// Constructor
Stack::Stack()
{
    head = NULL;
    tail = NULL;
}

// Adds a vertex to the stack
void Stack::push(string name)
{
    StackNode* n = new StackNode; //the new node for the new value
    n->key = name;
    n->next = NULL;     //preseting for good practices
    n->prev = NULL;
    if(head == NULL)    //if stack is empty (as soon as something is in stack then head will not be NULL)
    {
        head = n;
        tail = n;
    }
    else
    {
        tail->next = n; //the next from current tail points to new node, n
        n->prev = tail; //the previous will point to old tail
        tail = n;       //update tail to point at our node
    }
}

// Pops and returns a string from the stack
string Stack::pop()
{
    if(head == NULL)        //if stack is empty
        return NULL;
    StackNode* temp = tail;		//temporary value for the current tail
    if(head == tail)        //if there is only one node in the list
    {
        delete head;
        head = NULL;
        tail = NULL;
        return temp->key;
    }
        tail = tail->prev;  //the tail is now the previous node to tail
        delete tail->next;
        tail->next = NULL;  //new tail now points to NULL
        return temp->key;
}

// Prints the stack from top to bottom
void Stack::printTopToBottom()
{
    StackNode* temp = tail;
    if(tail == NULL)
    {
        //cout << "The stack is empty.";
    }
    while(temp)
    {
        cout << temp->key << " -> ";
        temp = temp->prev;  //traversing the stack backwards

    }
}
/*===================================END OF STACK CLASS====================================*/


/*==================================START OF GRAPH CLASS===================================*/
//constructor
CityGraph::CityGraph()
{
	vertices = new Array(2);
}

//destructor
CityGraph::~CityGraph()
{
	//deleteGraph();
}

// Upon program start, the user will pass the name of the text file containing all city graph information
// The file contains the names of the cities and the distances between them stored as an adjacency matrix
// The insertCities method opens the file and reads all thee data to build the graph
void CityGraph::insertCities(string fileName)
{
	//reading the file
	ifstream in(fileName);
    if (!in)
    {
        cout << "File can't be opened! " << endl;
        exit(1);
    }

    //reading the first line of city vertices
    string cityline1;
    getline(in, cityline1);
    stringstream st(cityline1);

	//reading individual city names from the first line
	string cityname;
    while(getline(st, cityname, ','))
    {
    	if(cityname != "cities")
    	{
    		//initializing a new vertex
    		CityVertex* cv = new CityVertex;
    		cv->name = cityname;
    		cv->ll = NULL;
    		cv->visited = false;
    		cv->ID = -1;
    		cv->parent = NULL;
    		cv->pathDistance = 0;

    		//adding the vertex to the array of vertices
    		vertices->arrayInsert(citycount, cv);
    		citycount++;
    	}
    }
    //the last number in the cities list is the infection parameter
    int infectionParam = stoi(cityname);
    //the city count is one less because of the infection parameter
    citycount--;
    //cout << "infection parameter: " << infectionParam << endl;
    
    //reading adjacency list info
    string cityline2;
    while(getline(in, cityline2))
    {
    	stringstream st(cityline2);

	    string citydata;
	    string vertexname;
	    bool infected;
	    for(int i = 0; i <= citycount+1; i++)
	    {
	    	getline(st, citydata, ',');
	    	if(i == 0)
	    	{
	    		//setting the vertex name to the name from the file
	    		vertexname = citydata;
	    	}
	    	else if(i == 1)
	    	{
	    		string infection = citydata;
	    		if(infection.compare("S"))
	    			infected = false;
	    		else
	    			infected = true;
	    	}
	    	else
	    	{
	    		int dist = stoi(citydata);
	    		if(dist != -1 && dist != 0)
	    		{
	    			//First we find the vertex and adjacent city in the array
	    			CityVertex* vert = vertices->arraySearch(vertexname);
	    			CityVertex* adj = vertices->arraySearch(vertices->get(i-2)->name);
	    			vert->infected = infected; //setting the infection parameter

	    			if(vert->ll == NULL) //if the list is empty (head pointer is null)
	    			{
	    				//initializing a new linked list
	    				vert->ll = new LinkedList;
	    				vert->ll->append(adj, dist);
	    			}
	    			else //established linked list
	    			{
	    				//adding that adjacent city to the linked list of adjacent cities for the vertex
	    				vert->ll->append(adj, dist);
	    			}
	    		}
	    	}
	    }
    }
}

// Taking in two vertices, this method checks to see if they are adjacent
bool CityGraph::isAdjacent(string v1, string v2)
{
	bool adj = false;
	CityVertex* vert = vertices->arraySearch(v1);
	AdjacentCity* curr;
	if(vert != NULL)
	{
		//starting at the head of the first city's linked list if the string exists
		curr = vert->ll->gethead();
	}
	else
	{
		return false;
	}

	while(curr != NULL)
	{
		//if the current name matches the name of the second city
		if(curr->vertex->name.compare(v2) == 0)
		{
			adj = true;
			break;
		}
		else
		{
			curr = curr->next;
		}
	}
	return adj;
}

// findDistricts performs a depth-first search to determine connected cities, and assign those cities a district ID
// districts are cities either connected directly by an edge or indirectly by another vertex
// a district ID from 1 to n is maintianed for each vertex
void CityGraph::findDistricts()
{
	int districtCount = 1;
	for(int i = 0; i < citycount; i++)
	{
		//cout << "Current Vertex: " << vertices->get(i)->name << endl;
		if(!vertices->get(i)->visited) //if the vertex has not been visited
		{
			DFS_helper(vertices->get(i), districtCount);
			districtCount++;
		}
	}
}

void CityGraph::DFS_helper(CityVertex* vertex, int district)
{
	vertex->visited = true;
	vertex->ID = district;

	// traversing the adjacent linked list
	AdjacentCity* tmp = vertex->ll->gethead();
	while(tmp != NULL)
	{
		if(!tmp->vertex->visited) //if the adj city has not been visited
		{
			//cout << "\nWe are on " << vertex->name << endl;
			//cout << "adjacent vertex not visited: " << tmp->vertex->name << endl;
			DFS_helper(tmp->vertex, district);
		}
		tmp = tmp->next;
	}
}

// When this options is selected, the user is promted for the names of two cities
// If the cities are in the different districts, "No safe path between cities"
// If the cities are in the same district, a breadth-first search is executed
// And the number and name of edges along the shortes path are returned
void CityGraph::findShortestPath(string city1, string city2)
{
	//finding the verices and reseting everything along the way
	CityVertex* v1 = NULL;
	CityVertex* v2 = NULL;
	for(int i = 0; i < citycount ; i++)
	{
		if(vertices->get(i)->name == city1) 
			v1 = vertices->get(i);
		if(vertices->get(i)->name == city2) 
			v2 = vertices->get(i);
		vertices->get(i)->visited = false;
		vertices->get(i)->pathDistance = 0;
		vertices->get(i)->parent = NULL;
	}

	//checking to see if the cities exist
	if(v1 == NULL || v2 == NULL)
	{
		cout << "\nOne or more cities doesn't exist" << endl;
		return;
	}

	//checking if they have districts assigned
	if(v1->ID == -1 || v2->ID == -1)
	{
		cout << "\nPlease identify the districts (option 2) before finding the shortest path" << endl;
		return;
	}

	if(v1->ID == v2->ID) //if they are in the same district, we are good to search
	{
		//Breadth-First Search:
		//mark the start as visited with a distance of 0
		v1->visited = true;
		v1->pathDistance = 0;

		//Creating a queue to store the vertices that need to be checked
		Queue queue;
		queue.enqueue(v1);

		//Initializing an array to store the path
		Array* a = new Array(1);
		int count = 0;

		CityVertex* last;
		while(!queue.isEmpty())
		{
			//traversing the adjacency list of the vertex dequeued from the queue
			CityVertex* vert = queue.dequeue();
			AdjacentCity* curr = vert->ll->gethead();
			while(curr != NULL)
			{
				if(!curr->vertex->visited) //if the vertex has not been visited
				{
					curr->vertex->pathDistance = vert->pathDistance + 1;
					curr->vertex->parent = vert;
					//cout << "\nvertex: " << curr->vertex->name << " parent: " << vert->name;
					if(curr->vertex == v2)
					{
						curr->vertex->visited = true;
						last = curr->vertex;
						CityVertex* temp = curr->vertex->parent;
						//adding the path of parent pointers to the array
						while(temp != NULL)
						{
							a->arrayInsert(count, temp);
							temp = temp->parent;
							count++;
						}
						break;
					}
					else
					{
						curr->vertex->visited = true;
						queue.enqueue(curr->vertex);
					}
				}
				else
				{
					curr = curr->next;
				}
			}
		}
		//Printing the distance and the path of parent pointers backwards
		cout << "\n" << last->pathDistance << ": ";
		for(int i = count-1; i >= 0; i--)
		{
			cout << a->get(i)->name << " -> ";
		}
		cout << last->name << endl;
	}
	else
	{
		cout <<  "\nNo safe path between cities" << endl;
		return;
	}
}

// This option prompts for the names of two cities and determines if they are in the same district
// If the cities are in different districts, “No safe path between cities” is printed
// If the cities are in the same district, Dijkstra’s algorithm finds the shortest distance between the cities
// Both the distance and the names of vertices along the path are printed
void CityGraph::findShortestWeightedPath(string city1, string city2)
{
	//finding the verices
	CityVertex* v1 = NULL;
	CityVertex* v2 = NULL;
	for(int i = 0; i < citycount ; i++)
	{
		if(vertices->get(i)->name == city1) 
			v1 = vertices->get(i);
		if(vertices->get(i)->name == city2) 
			v2 = vertices->get(i);
		vertices->get(i)->visited = false;
		vertices->get(i)->pathDistance = 0;
		vertices->get(i)->parent = NULL;
	}

	//checking to see if the cities exist
	if(v1 == NULL || v2 == NULL)
	{
		cout << "\nOne or more cities doesn't exist" << endl;
		return;
	}

	//checking if they have districts assigned
	if(v1->ID == -1 || v2->ID == -1)
	{
		cout << "\nPlease identify the districts (option 2) before finding the shortest path" << endl;
		return;
	}

	if(v1->ID == v2->ID) //if they are in the same district, we are good to search
	{
		//Dijkstra's Algorithm:
		//Initializing an array to store the list of solved vertices
		Array* solved = new Array(1);

		//marking the start as solved with distance of 0
		v1->visited = true;
		v1->pathDistance = 0;

		//adding the first vertex to the solved array and starting the count at 1
		solved->arrayInsert(0, v1);
		int solvedCount = 1; //the array size

		CityVertex* solvedV = NULL; //new CityVertex;
		CityVertex* parent = NULL;
		CityVertex* temp = NULL;
		AdjacentCity* curr = NULL;
		while(!v2->visited)
		{
			int minDistance = 100000;
			int dist;
			solvedV = NULL;
			
			//traversing the solved vertices array (for all solved vertices)
			for(int i = 0; i < solvedCount; i++)
			{
				temp = solved->get(i);
				//cout << "\ntemp: " << temp->name << endl;

				//for each solved vertex, we traverse its adjacency list
				curr = temp->ll->gethead();
				while(curr != NULL)
				{
					//cout << "curr: " << curr->vertex->name << endl;
					if(!curr->vertex->visited) //if the current vertex has not been visited
					{
						//curr->vertex->visited = true;
						dist = temp->pathDistance + curr->distance;
						//cout << "\ntotDistance = " << temp->pathDistance << " + " << curr->distance << " = " << dist << endl;
						//cout << "minDistance = " << minDistance << endl;
						if(dist < minDistance)
						{
							//solved becomes the current vertex
							solvedV = curr->vertex;
							//the minimum distance becomes this distance cuz it's less
							minDistance = dist;
							//and the parent is set to temp
							parent = temp;
						}
						curr = curr->next;
					}
					else
					{
						curr = curr->next;
					}
				}
			}
			solvedV->pathDistance = minDistance;
			solvedV->visited = true;
			solvedV->parent = parent;
			solved->arrayInsert(solvedCount, solvedV);
			solvedCount++;
			//cout << "solved: " << solvedV->name << " with parent " << solvedV->parent->name << " (" << solvedV->parent << endl;
		}
		
		//Implementing a stack to print the path backward
		Stack stack;

		CityVertex* current = v2->parent;
		string name;
		while(current->parent != NULL)
		{
			name = current->name;

			//pushing names onto the stack and moving along
			stack.push(name);
			current = current->parent;
		}
		
		//Printing
		cout << "\n" << v2->pathDistance << ": ";
		cout << v1->name << " -> ";
		stack.printTopToBottom();
		cout << v2->name;
	}
	else
	{
		cout << "No safe path between cities" << endl;
	}
}

// The adjacency matrix contains an infection parameter that acts as an indicator variable to determine whether a city has been infected
// When the user selects this option, an infection process begins at t = 0
// For the first time step, any existing cities that are infected will begin infecting their adjacent neighbors
// In a single time step, a city may only be infected if one of its neighbors was already infected at the start of that time step
// The number of time steps the graph took to allow the zombie infection to run its course is output
int CityGraph::zombieInfection()
{
	int t = 0;
	bool running = true;
	Queue queue; //queue to store all the infected cities
	
	//first we reset all the infection parameters for the start
	for(int i = 0; i < citycount; i++)
	{
		CityVertex* vert = vertices->get(i);
		if(vert->infected) //if the city is infected @start
		{
			//we set its parameter to true and add it to the queue
			vert->infection = true;
		}
		else
		{
			vert->infection = false;
		}
	}

	//then at every timestep, we infect all of its neighboring cities
	while(running)
	{
		//incrementing the time step
		t++;

		//traversing all the vertices
		for(int i = 0; i < citycount; i++)
		{
			CityVertex* vert = vertices->get(i);

			//if the vertex is already infected, then we infect its neighbors
			if(vert->infection)
			{
				running = infectNeighbors(vert);
				//if(!running && t == 0)
				//	return 0;
			}
		}

		//then after traversing all the vertices, all the temporary infections turn to permanent ones for the next 
		for(int i = 0; i < citycount; i++)
		{
			CityVertex* vert = vertices->get(i);
			if(vert->tempinfection) //if the vertex is temporarily infected, then we cement that
			{
				vert->infection = true;
			}
		}
	}
	return t;
}

// Infects adjacent cities given a vertex
bool CityGraph::infectNeighbors(CityVertex* vert)
{
	bool foundInfected = false; //if we find a new city to infect, this will become true

	AdjacentCity* curr = vert->ll->gethead();
	while(curr != NULL)
	{
		//cout << "curr: " << curr->vertex->name << endl;
		if(curr->vertex->infection == false) //if it is not already infected
		{
			//then we temp infect that city and move on
			//cout << "not infected yet" << endl;
			curr->vertex->tempinfection = true;
			curr = curr->next;
			foundInfected = true;
		}
		else //if it is already infected, then we move on to the next
		{
			//cout << "not infected" << endl;
			curr = curr->next;
		}
	}
	//cout << "foundInfected: " << foundInfected << endl;
	return foundInfected;
}

// Prints the vertices and adjacent vertices
void CityGraph::printVertices()
{
	for(int i = 0; i < citycount; i++)
	{
		CityVertex* vert = vertices->get(i);
		//cout << vert->visited << ":";
		cout << vert->ID << ":";
		cout << vert->name << ": ";
		vert->ll->traverse();
		cout << endl;
	}
}
/*===================================END OF GRAPH CLASS====================================*/

