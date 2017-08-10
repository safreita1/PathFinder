/*
 * AdjacencyList.h
 *
 *  Created on: Jan 18, 2016
 *      Author: Scott Freitas
 */

#ifndef ADJACENCYLIST_H_
#define ADJACENCYLIST_H_

#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator> 
#include <iostream>
#include <fstream>
#include <utility>
#include <set>
#include <map>

/**
 * This class creates an array of linked lists to store data.
 * The functions contained in it allow you to manipulate this array.
 */
class AdjacencyList {
public:

	/**
	 * Default constructor that creates an adjacency list.
	 */
	AdjacencyList();
	
	/**
	 * Constructor that creates an adjacency list.
	 * @parameter size  Determines the size of the adjacency list
	 */
	AdjacencyList(int size);

	/**
	 * Constructor that creates an adjacency list. The parameter
	 * size may be higher than vertexCount since not all vertices entered
	 * are not required to be in numerical order.
	 * @parameter size  Determines the size of the adjacency list
	 * @parameter vertexCount  The number of vertices in the outer vector list
	 */
	AdjacencyList(int size, int vertexCount);

	/**
	 * Constructor that creates an adjacency list. The parameter
	 * size may be higher than vertexCount since not all vertices entered
	 * are not required to be in numerical order.
	 * @parameter size  Determines the size of the adjacency list
	 * @parameter vertexCount  The number of vertices in the outer vector list
	 */
	void resizeAdjList(int size, int vertexCount);

	/**
	 * Removes an edge from the adjacencyList.
	 * @parameter firstVertex  The first half of the edge.
	 * @parameter secondVertex  The second half of the edge.
	 */
	void removeEdge(int firstVertex, int secondVertex);

	/**
	 * Adds an edge to the adjacencyList.
	 * @parameter firstVertex  The first half of the edge.
	 * @parameter secondVertex  The second half of the edge.
	 */
	void addEdge(int firstVertex, int secondVertex);

	/**
	 * Changes the value of a vertex in the infoList.
	 * @parameter vertexToUpdate  The vertex to update in the infoList.
	 * @parameter secondVertex  The second half of the edge.
	 */
	void updateInfo(int vertexToUpdate, int value);
	
	/**
	 * Gets the value of a given vertex 
	 * @parameter vertex  The vertex that you want to look up.
	 * @return an integer that contains the value of a vertex.
	 */
	int getInfoValue(int vertex) const;

	/**
	 * Adds all the vertices in verticesToAdd to the adjacencyList at vertex
	 * @parameter vertex  The vertex add connections to.
	 * @parameter vericesToAdd  Vector of vertices to add.
	 */
	void setVertexConnections(int vertex, std::vector<int>& vericesToAdd);

	/**
	 * Gets a vector of vertices at a given vertex in the adjacency list.
	 * @parameter vertex  The vertex that you want to look up.
	 * @return a vector<int> that contains the edges connected to a
	 * given vertex.
	 */
	std::vector<int> getVertexConnections(int vertex) const;

	/**
	 * Gets the number of edges a given vertex has.
	 * @parameter vertex  The vertex that you want to look up.
	 * @return an integer that contains the number of connections
	 * for the given vertex.
	 */
	int getVertexConnectionCount(int vertex) const;

	/**
	 * Gets the value at the given vertex and index in the adjacencyList.
	 * @parameter vertex  The vertex in the adjacencyList to look at.
	 * @parameter index  The position to get the value from.
	 * @return an integer which is the value at the given vertex and index.
	 */
	int getVertexData(int vertex, int index) const;

	/**
	* Checks to see if a given vertex is within in the adjacency list.
	* @parameter vertex The vertex to search the adjacency list for.
	* @return True if the vertex is valid, False otherwise.
	*/
	bool validVertex(int vertex) const;

	/**
	 * Gets the size of the adjacencyList. 
	 * @return an integer that contains the size of the adjacencyList.
	 */
	int size() const;

	/**
	 * Gets the number of vertices in the adjacencyList. 
	 * @return an integer that contains the number of vertices in the 
	 * adjacencyList.
	 */
	int vertexCount() const;

	/**
	 * Gets a string containing the information in the adjacencyList.
	 * @return a string that contains the information in the adjacencyList.
	 */
	std::string displayAdjacencyList() const;

	/**
	 * Saves the adjacencyList to a file.
	 * @parameter useNameList Determines whether or not to save the
	 * information with name or integer values.
	 * @parameter nameList The map of integers to names to use if
	 * useNameList is True.
	 * @parameter path The path to save the file too. The path must 
	 * include the file name.
	 */
	void saveToFile(bool useNameList, std::map<int, std::string> nameList, std::string path);

private:
	std::vector<std::vector<int>> adjacencyList;
	//Connection Count or hops away = 1: color1, CC = 2: color2, CC = 3: color3, CC >= 4: color4
	std::vector<int> infoList;
	int highestVertex;
	int numberOfVertices;
};

#endif