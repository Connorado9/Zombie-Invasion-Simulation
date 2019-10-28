// Connor Humiston
// Godley 310
// Data Structures
// Final Project: A Nation Divided

// This file is where the following classes their methods are implemented
//   - Linked List Class
//   - Array Class
//   - Graph class

#include "CityGraph.hpp" //including the the other declarations
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

    		//adding the vertex to the array of vertices
    		vertices->arrayInsert(citycount, cv);
    		citycount++;
    	}
    }
    
    //reading adjacency list info
    string cityline2;
    while(getline(in, cityline2))
    {
    	stringstream st(cityline2);

	    string citydata;
	    string vertexname;
	    for(int i = 0; i <= citycount; i++)
	    {
	    	getline(st, citydata, ',');
	    	if(i == 0)
	    	{
	    		//setting the vertex name to the name from the file
	    		vertexname = citydata;
	    		//cout << "We are currently on " << vertexname << "\'s adjacency list" << endl;
	    	}
	    	else
	    	{
	    		int dist = stoi(citydata);
	    		if(dist != -1 && dist != 0) //|| (dist != -1))
	    		{
	    			//First we find the vertex and adjacent city in the array
	    			CityVertex* vert = vertices->arraySearch(vertexname);
	    			CityVertex* adj = vertices->arraySearch(vertices->get(i-1)->name);

	    			//cout << "\nvert is the vertex for " << vert->name << endl;
	    			//cout << "\nadj is the city for " << adj->name << endl;

	    			if(vert->ll == NULL) //if the list is empty (head pointer is null)
	    			{
	    				//initializing a new linked list
	    				//cout << "\n" << vertexname << "'s linked list was empty" << endl;
	    				vert->ll = new LinkedList;
	    				vert->ll->append(adj, dist);
	    				//cout << "\nso we have appended an adjacent city with vertex " << adj->name << " and distance " << dist << " to a new LL" << endl; 
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

// Adds cityVertex to the linked list
void CityGraph::insertVertex(CityVertex city)
{

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

// Deletes the cityVertex with the removeCityName
void CityGraph::deleteVertex(string removeCityName)
{

}

// Inserts an edge between the firstCity and secondCity, along with assigning a distance
void CityGraph::insertEdge(string firstCity, string secondCity, int distance)
{

}

// Deletes the edge connecting the firstCity and secondCity inputs
void CityGraph::deleteEdge(string firstCity, string secondCity)
{

}

// Prints the vertices and adjacent vertices
void CityGraph::printVertices()
{
	for(int i = 0; i < citycount; i++)
	{
		CityVertex* vert = vertices->get(i);
		cout << vert->name << ": ";
		vert->ll->traverse();
		cout << endl;
	}
}

// Returns a CityVertex with the passed cityName
CityVertex* CityGraph::searchGraph(string cityName)
{
	CityVertex* vertex = new CityVertex;
	return vertex;
}
/*===================================END OF GRAPH CLASS====================================*/

