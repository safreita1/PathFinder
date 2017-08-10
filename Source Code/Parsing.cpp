/*
 * Parsing.cpp
 *
 *  Created on: N/A
 *      Author: Scott Freitas
 */

#include "Parsing.h"

void Parsing::getGraphData(std::string pathToDataSetFile, AdjacencyList &adjacencyList) {
	std::vector <int> firstEdgeSet;
	std::vector <int> secondEdgeSet;
	int firstNumber, secondNumber = 0;
	int highestNumber = 0;
	int numberOfVertices = 0;
	int temp = 0;

	FILE *f = fopen(pathToDataSetFile.c_str(), "r");

	//Check for invalid file
	if (f == NULL) {
		//std::cout << "Error Reading File." << std::endl;
		exit(1);
	}

	fscanf(f, "%d", &numberOfVertices);
	fscanf(f, "%d", &temp);

	while (fscanf(f, "%d" "%d", &firstNumber, &secondNumber) != EOF) {

		if (firstNumber > highestNumber) {
			highestNumber = firstNumber;
		}

		if (secondNumber > highestNumber) {
			highestNumber = secondNumber;
		}

		firstEdgeSet.push_back(firstNumber);
		secondEdgeSet.push_back(secondNumber);
	}

	//Allocate memory for the vertices
	adjacencyList.resizeAdjList(highestNumber + 1, numberOfVertices);

	for (int index = 0; index < firstEdgeSet.size(); index++) {
		adjacencyList.addEdge(firstEdgeSet.at(index), secondEdgeSet.at(index));
	}

	//Close the file
	fclose(f);
	f = NULL;
}


void Parsing::getNamedGraphData(std::string pathToDataSetFile, AdjacencyList &adjacencyList, 
								std::unordered_map<int, std::string> &nameList, std::unordered_map<std::string, int> &nameListKey) {

	std::vector <int> firstEdgeSet;
	std::vector <int> secondEdgeSet;
	char firstName[100];
	char secondName[100];
	//NumberOfNames and nameCount should end up being the same value
	int numberOfNames = 0;
	int nameCount = 0;
	int temp = 0;

	FILE *f = fopen(pathToDataSetFile.c_str(), "r");

	//Check for invalid file
	if (f == NULL) {
		//std::cout << "Error Reading File." << std::endl;
		exit(1);
	}

	fscanf(f, "%d", &nameCount);
	fscanf(f, "%d", &temp);
	
	//Allocate memory for the vertices
	adjacencyList.resizeAdjList(nameCount, nameCount);

	while (fscanf(f, "%s" "%s", firstName, secondName) != EOF) {
		//If the first name is not in the set, add it to the list and set
		if (nameListKey.count(firstName) == 0) {
			nameListKey[firstName] = numberOfNames;
			nameList[numberOfNames] = firstName;
			numberOfNames++;
		}
		//If second name is not in the set, add it to the list and set
		if (nameListKey.count(secondName) == 0) {
			nameListKey[secondName] = numberOfNames;
			nameList[numberOfNames] = secondName;
			numberOfNames++;
		}

		adjacencyList.addEdge(nameListKey[firstName], nameListKey[secondName]);
	}

	//Close the file
	fclose(f);
	f = NULL;
}

void Parsing::removeVertices(AdjacencyList &adjacencyList, const std::unordered_map<std::string, int> &nameListKey, 
								const std::vector<std::string> &programInfo, bool useNameList) {

	std::vector<int> removeVertices;
	//Get the vertices to remove from the graph
	for (int index = 24; index < 29; index++) {
		if (useNameList) {
			if (nameListKey.count(programInfo.at(index))) {
				removeVertices.push_back(nameListKey.at(programInfo.at(index)));
			}
		}
		else {
			int vertex = stoi(programInfo.at(index));
			if (vertex != -1) {
				removeVertices.push_back(vertex);
			}
		}
	}

	//Remove the vertices and their edges from the adjacency list
	for (int index = 0; index < removeVertices.size(); index++) {
		//Check to see that the vertex exists in the adj. list before removing connections
		if (adjacencyList.validVertex(removeVertices.at(index))) {
			std::vector<int> connections = adjacencyList.getVertexConnections(removeVertices.at(index));
			//Loop through each vertex connected to the vertex to be removed
			for (int connectionIndex = 0; connectionIndex < connections.size(); connectionIndex++) {
				//Remove the associated edge
				adjacencyList.removeEdge(removeVertices.at(index), connections.at(connectionIndex));
			}
		}
	}
}

void Parsing::removeEdges(AdjacencyList &adjacencyList, const std::unordered_map<std::string, int> &nameListKey, 
							const std::vector<std::string> &programInfo, bool useNameList) {

	std::vector<int> removeEdges;
	//Get the edges to remove from the graph
	for (int index = 37; index < 42; index++) {
		if (useNameList) {
			if (nameListKey.count(programInfo.at(index))) {
				removeEdges.push_back(nameListKey.at(programInfo.at(index)));
			}
		}
		else {
			int vertex = stoi(programInfo.at(index));
			if (vertex != -1) {
				removeEdges.push_back(vertex);
			}
		}
	}

	//Loop through and remove the edges from the adjacency list
	for (int index = 0; index < removeEdges.size(); index = index + 2) {
		//Check that the vertices exist before removing the edge
		if (adjacencyList.validVertex(removeEdges.at(index)) && adjacencyList.validVertex(removeEdges.at(index + 1))) {
			adjacencyList.removeEdge(removeEdges.at(index), removeEdges.at(index + 1));
		}
	}
}

void Parsing::parseMSTResults(const std::vector<PathInformation> &mstShortestPaths, const std::vector<int> &MSTVertices, 
								std::vector<std::vector<int>> &keyVertices, std::ofstream &output) {

	double avgPathLength = 0;
	//Display the MST path
	for (int index = 0; index < mstShortestPaths.size(); index++) {
		output << "Length of path " << index << ": " << mstShortestPaths.at(index).getPathLength() << std::endl;
		avgPathLength += (double)mstShortestPaths.at(index).getPathLength();
	}
	output << "Average path length: " << (double)(avgPathLength / mstShortestPaths.size()) << std::endl;

	//Insert the MST vertices
	keyVertices[0] = MSTVertices;

	//Insert the path vertices
	for (int pathIndex = 0; pathIndex < mstShortestPaths.size(); pathIndex++) {
		for (int index = 0; index <= mstShortestPaths.at(pathIndex).getPathLength(); index++) {
			keyVertices[1].push_back(mstShortestPaths.at(pathIndex).getPathAt(index));
		}
	}

	//Sort the vertices
	std::sort(keyVertices.at(0).begin(), keyVertices.at(0).end());
	std::sort(keyVertices.at(1).begin(), keyVertices.at(1).end());

	//Ensure that only unique vertices are in the path vertices
	keyVertices.at(1).erase(unique(keyVertices.at(1).begin(), keyVertices.at(1).end()), keyVertices.at(1).end());

	//Remove the MST vertices from the path vertices
	for (int tempIndex = 0; tempIndex < keyVertices[0].size(); tempIndex++) {
		keyVertices[1].erase(remove(keyVertices[1].begin(), keyVertices[1].end(), keyVertices[0].at(tempIndex)), keyVertices[1].end());
	}
}

void Parsing::parseKSSPResults(std::vector<std::vector<int>> &keyVertices, const std::vector<PathInformation> &shortestPaths, 
	int startVertex, int endVertex) {
		
	//Insert the start and end vertices
	keyVertices.at(0).push_back(startVertex);
	keyVertices.at(0).push_back(endVertex);

	//Insert the path vertices
	for (int pathIndex = 0; pathIndex < shortestPaths.size(); pathIndex++) {
		for (int index = 0; index <= shortestPaths.at(pathIndex).getPathLength(); index++) {
			keyVertices.at(1).push_back(shortestPaths.at(pathIndex).getPathAt(index));
		}
	}

	//Sort the vertices
	std::sort(keyVertices.at(0).begin(), keyVertices.at(0).end());
	std::sort(keyVertices.at(1).begin(), keyVertices.at(1).end());

	//Ensure that only unique vertices are in the path vertices
	keyVertices.at(1).erase(unique(keyVertices.at(1).begin(), keyVertices.at(1).end()), keyVertices.at(1).end());

	//Remove the start and end vertices from the path vertices
	for (int tempIndex = 0; tempIndex < keyVertices[0].size(); tempIndex++) {
		keyVertices[1].erase(remove(keyVertices[1].begin(), keyVertices[1].end(), keyVertices[0].at(tempIndex)), keyVertices[1].end());
	}
}
