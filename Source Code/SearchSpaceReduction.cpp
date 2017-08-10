/*
 * SearchSpaceReduction.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: scott
 */

#include "SearchSpaceReduction.h"

void SearchSpaceReduction::searchSpaceReduce(const AdjacencyList &adjacencyList, AdjacencyList &reducedAdjacencyList, 
												const PathInformation &pathToSearch, int depthToSearch, int numVerticesFirstIter, 
												int numVerticesSubsequentIter, int criticalVerticesNextIter) {
		
	int averageCentrality = 0;
	int emptyAdjacencyListCounter = 0;

	//Get the average centrality of the graph
	for (int index = 0; index < adjacencyList.size(); index++) {
		if (adjacencyList.getVertexConnectionCount(index) > 0) {
			averageCentrality += adjacencyList.getVertexConnectionCount(index);
		}
		else {
			emptyAdjacencyListCounter++;
		}
	}

	//Calculate the average vertex centrality
	averageCentrality = (averageCentrality / (adjacencyList.size() - emptyAdjacencyListCounter));

	//If the user is attempting to search for all the vertices, reduce the average centrality to 0
	if (numVerticesFirstIter == 100000 && numVerticesSubsequentIter == 100000 && criticalVerticesNextIter == 100000 && depthToSearch >= 2) {
		averageCentrality = 0;
	}

	int currentDepth = 1;
	//Reduce the graph size based on a vertex centrality heuristic
	SearchSpaceReduction::keyNeighboringVertices(adjacencyList, pathToSearch, reducedAdjacencyList, currentDepth, 
		depthToSearch, averageCentrality, numVerticesFirstIter, numVerticesSubsequentIter, criticalVerticesNextIter);
}

void SearchSpaceReduction::keyNeighboringVertices(const AdjacencyList &adjacencyList, const PathInformation &pathToSearch, 
											AdjacencyList &updatedAdjacencyList, int &currentDepth, int depthToSearch, 
											int averageCentrality, int numVerticesFirstIter, int numVerticesSubsequentIter, 
											int criticalVerticesNextIter) {

	int numberOfElementsToTake = numVerticesFirstIter;

	//Array to store the number of shortest path vertices that each vertex in the bin contains
	std::vector<std::vector<int>> shortestPathVertexBin(pathToSearch.getPathLength() + 1);
	
	//Only run this heuristic if the shortest path length is >= to 1
	if (pathToSearch.getPathLength() >= 1) {

		//Place the index of the reduced adjacency list into a bin based on the number of connections the reduced adjacency 
		//list vertex had to the shortest path vertex's
		for (int index = 0; index < adjacencyList.size(); index++) {
			//Get the number of connections each vertex has
			if (adjacencyList.getVertexConnectionCount(index) > averageCentrality) {
				//Loop through each vertex in the path and get each of it's neighboring vertices
				for (int binIndex = 0; binIndex <= pathToSearch.getPathLength(); binIndex++) {
					//If an edge of the current vertex has a match with a path vertex, identify it
					if (Utility::vectorIntIntersection(adjacencyList.getVertexConnections(index), pathToSearch.getPathAt(binIndex))) {
						shortestPathVertexBin[binIndex].push_back(index);
					}
				}
			}
		}

		//Sort the path vertices' neighboring vertices in descending order of vertex centrality  
		std::vector<std::vector <std::pair<int, int> > > dataToSort(pathToSearch.getPathLength() + 1);

		for (int pathVertex = 0; pathVertex < shortestPathVertexBin.size(); pathVertex++) {
			for (int index = 0; index < shortestPathVertexBin[pathVertex].size(); index++) {
				dataToSort.at(pathVertex).push_back(std::make_pair(shortestPathVertexBin[pathVertex].at(index), 
													adjacencyList.getVertexConnectionCount(shortestPathVertexBin[pathVertex].at(index))));
			}

			sort(dataToSort.at(pathVertex).begin(), dataToSort.at(pathVertex).end(), sort_func());
		}

		//If the depth is 1 or greater, reduce the number of elements to sample
		if (currentDepth > 0) {
			numberOfElementsToTake = numVerticesSubsequentIter;
		}

		//For each path vertex, add it's top 'x' VC vertices to the new reduced adjacency list

		//Loop through each bin
		for (int currentBin = 0; currentBin <= pathToSearch.getPathLength(); currentBin++) {

			//Loop through each vertex up to the first �x� many
			for (int index = 0; index < dataToSort.at(currentBin).size() && index < numberOfElementsToTake; index++) {

				//If there is no existing connection between the two vertices, add it (aka, no duplicate connections)
				if (Utility::vectorIntIntersection(updatedAdjacencyList.getVertexConnections(dataToSort.at(currentBin).at(index).first), 
					pathToSearch.getPathAt(currentBin)) == false) {

					updatedAdjacencyList.addEdge(pathToSearch.getPathAt(currentBin), dataToSort.at(currentBin).at(index).first);

					//If the vertex doesn't have a color, give it one
					if (updatedAdjacencyList.getInfoValue(dataToSort.at(currentBin).at(index).first) == 0) {
						updatedAdjacencyList.updateInfo(dataToSort.at(currentBin).at(index).first, currentDepth);
					}
				}
			}
		}

		if (currentDepth < depthToSearch) {
			currentDepth++;

			PathInformation nextPath = PathInformation();
			std::vector<int> tempPath;

			for (int index = 0; index < dataToSort.size(); index++) {
				for (int vertexIndex = 0; vertexIndex < dataToSort.at(index).size() && vertexIndex < criticalVerticesNextIter; vertexIndex++) {
					tempPath.push_back(dataToSort.at(index).at(vertexIndex).first);
				}
			}

			nextPath.setPath(tempPath);
			nextPath.setPathLength(tempPath.size() - 1);

			keyNeighboringVertices(adjacencyList, nextPath, updatedAdjacencyList, currentDepth, depthToSearch, averageCentrality, 
										numVerticesFirstIter, numVerticesSubsequentIter, criticalVerticesNextIter);
		}
	}
}