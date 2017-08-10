/*
 * AdjacencyList.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: Scott Freitas
 */

#include "AdjacencyList.h"


AdjacencyList::AdjacencyList() {
}

AdjacencyList::AdjacencyList(int highestVertex) {
	this->highestVertex = highestVertex;
	this->numberOfVertices = highestVertex;
	adjacencyList.resize(highestVertex);
	infoList.resize(highestVertex);
}

AdjacencyList::AdjacencyList(int highestVertex, int numberOfVertices) {
	this->highestVertex = highestVertex;
	this->numberOfVertices = numberOfVertices;
	adjacencyList.resize(highestVertex);
	infoList.resize(highestVertex);
}

void AdjacencyList::resizeAdjList(int highestVertex, int numberOfVertices) {
	this->highestVertex = highestVertex;
	this->numberOfVertices = numberOfVertices;
	adjacencyList.resize(highestVertex);
	infoList.resize(highestVertex);
}

void AdjacencyList::removeEdge(int firstVertex, int secondVertex) {	
	adjacencyList.at(firstVertex).erase(remove(adjacencyList.at(firstVertex).begin(), 
		adjacencyList.at(firstVertex).end(), secondVertex), adjacencyList.at(firstVertex).end());

	adjacencyList.at(secondVertex).erase(remove(adjacencyList.at(secondVertex).begin(), 
		adjacencyList.at(secondVertex).end(), firstVertex), adjacencyList.at(secondVertex).end());
}

void AdjacencyList::addEdge(int firstVertex, int secondVertex) {
	adjacencyList.at(firstVertex).push_back(secondVertex);
	adjacencyList.at(secondVertex).push_back(firstVertex);
}

void AdjacencyList::updateInfo(int vertexToUpdate, int value) {
	infoList.at(vertexToUpdate) = value;
}

int AdjacencyList::getInfoValue(int vertex) const {
	return infoList.at(vertex);
}

void AdjacencyList::setVertexConnections(int vertex, std::vector<int>& vericesToAdd) {
	adjacencyList.at(vertex).insert(adjacencyList.at(vertex).end(), vericesToAdd.begin(), vericesToAdd.end());
}

std::vector<int> AdjacencyList::getVertexConnections(int vertex) const {
	return adjacencyList.at(vertex);
}

int AdjacencyList::getVertexConnectionCount(int vertex) const {
	return adjacencyList.at(vertex).size();
}

int AdjacencyList::getVertexData(int vertex, int index) const {
	return adjacencyList.at(vertex).at(index);
}

bool AdjacencyList::validVertex(int vertex) const {
	bool validVertex = false;
	if (vertex < adjacencyList.size()) {
		validVertex = true;
	}
	return validVertex;
}

int AdjacencyList::size() const {
	return highestVertex;
}

int AdjacencyList::vertexCount() const {
	return numberOfVertices;
}

std::string AdjacencyList::displayAdjacencyList() const {
	std::string vertexConnections = "\n";

	for(int v = 0; v < highestVertex; v++) {
		std::stringstream vertex;
		std::stringstream convertedData;
		vertex << v;
		copy(adjacencyList.at(v).begin(), adjacencyList.at(v).end(), std::ostream_iterator<int>(convertedData, " "));
		vertexConnections = vertexConnections + vertex.str() + ": " + convertedData.str() + "\n";
	}
	vertexConnections = vertexConnections + "\n";

	return vertexConnections;
}

void AdjacencyList::saveToFile(bool useNameList, std::map<int, std::string> nameList, std::string fileLocation) {
	std::vector<std::pair <int, int> > edges;
	std::set<int> vertices;
	std::ofstream myfile;
	myfile.open(fileLocation);

	for (int v = 0; v < highestVertex; v++) {

		std::vector<int> vertexConnections = adjacencyList.at(v);
		
		for (int index = 0; index < vertexConnections.size(); index++) {
			std::pair<int, int> tempPair = std::make_pair(v, vertexConnections.at(index));
			std::pair<int, int> tempPairReversed = std::make_pair(vertexConnections.at(index), v);

			//Add vertex
			vertices.insert(vertexConnections.at(index));

			//Add edge if not already added
			if (find(edges.begin(), edges.end(), tempPair) == edges.end() && find(edges.begin(), edges.end(), 
				tempPairReversed) == edges.end()) {
					
				edges.push_back(tempPair);
			}
		}
	}

	//If not using names, save the number of vertices and edges
	if (!useNameList) {
		myfile << std::to_string(vertices.size()) + "\n";
		myfile << std::to_string(edges.size()) + "\n";
	}


	for (std::vector<std::pair< int, int> >::iterator it = edges.begin(); it != edges.end(); it++) {
		//Print the names instead of integers
		if (useNameList) {
			myfile << nameList.at(it->first) << " " << nameList.at(it->second) << std::endl;
		}
		//Otherwise, if no names print integers
		else {
			myfile << it->first << " " << it->second << std::endl;
		}

	}

	myfile.close();
}