/*
 * DijkstrasAlgorithm.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: Scott Freitas

 * References: 
 * (1) https://www.quora.com/What-is-the-most-simple-efficient-C++-code-for-Dijkstras-shortest-path-algorithm
 * A large part of this algorithm's code was based on Michal Forišek's answer
 */

#include "DijkstrasAlgorithm.h"

void DijkstrasAlgorithm::singleSourceShortestPath(int startVertex, int endVertex, AdjacencyList adjacencyList, PathInformation &pathInfo, 
													int firstEdgeToDelete, int secondEdgeToDelete, bool removeEdge) {
														
	std::set<std::pair<int,int>> nodesToSearch;
	std::vector<int> distance(adjacencyList.size(), std::numeric_limits<int>::max());
	std::unordered_map<int, int> parent;
	distance[startVertex] = 0;
	parent[startVertex] = 1000000;

	// If true, remove the edge from the adjacency list
	if (removeEdge) {
		adjacencyList.removeEdge(firstEdgeToDelete, secondEdgeToDelete);
	}

	//Initialize the list with the starting vertex
	nodesToSearch.insert( {0, startVertex} );

	//Keep searching while the priroity queue is not empty
	while (!nodesToSearch.empty()) {

		//Get the minimum node available
		int minNode = nodesToSearch.begin()->second;

		//Check to see if the goal has been reached
		if (minNode == endVertex) {
			break;
		}

		//Remove the minimum node from the priority queue
		nodesToSearch.erase( nodesToSearch.begin() );

		//Loop through all the successor nodes of the current node
		for (int v = 0; v < adjacencyList.getVertexConnectionCount(minNode); v++) {
			
			int neighbor = adjacencyList.getVertexData(minNode, v);
			int alt = distance.at(minNode) + 1;

			//Update the distance if a shorter path has been found
			if (alt < distance[neighbor]) {
				nodesToSearch.erase( {distance.at(neighbor), neighbor} );
				distance.at(neighbor) = alt;
				parent[neighbor] = minNode;
				nodesToSearch.insert( {distance.at(neighbor), neighbor} );
			}
		}
	}

	std::vector<int> pathTaken;
	int shortestPathLength = 0;

	//If there is a shortest path
	if (distance.at(endVertex) != std::numeric_limits<int>::max()) {
		shortestPathLength = distance.at(endVertex);

		//Display path taken
		pathTaken.push_back(endVertex);
		while (parent.at(endVertex) != 1000000) {
			pathTaken.push_back(parent.at(endVertex));
			endVertex = parent.at(endVertex);
		}
	}

	reverse(pathTaken.begin(), pathTaken.end());

	pathInfo.setPath(pathTaken);
	pathInfo.setPathLength(shortestPathLength);
}
