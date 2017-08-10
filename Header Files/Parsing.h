/*
 * Parsing.h
 *
 *  Created on: N/A
 *      Author: Scott Freitas
 */

#ifndef PARSING_H_
#define PARSING_H_
#define _CRT_SECURE_NO_WARNINGS

#include <AdjacencyList.h>
#include <PathInformation.h>

#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdio.h>


class Parsing {
public:
	/**
	 * Reads in integer graph data.
	 * @parameter pathToDatasetFile Path to the dataset.
	 * @parameter adjacencyList Data structure to hold all
	 * the dataset information.
	*/
	static void getGraphData(std::string pathToDatasetFile, AdjacencyList &adjacencyList);

	/**
	 * Reads in string graph data.
	 * @parameter pathToDatasetFile Path to the dataset.
	 * @parameter adjacencyList Data structure to hold all
	 * the dataset information.
	 * @parameter nameList Creates a map between the integer and string 
	 * representation of the data.
	 * @parameter nameListKey Creates a map between the string and integer 
	 * representation of the data.
	*/
	static void getNamedGraphData(std::string pathToDataSetFile, AdjacencyList &adjacencyList, std::unordered_map<int, std::string> &nameList, 
									std::unordered_map<std::string, int> &nameListKey);

	/**
	 * Removes user specified vertices from the adjacency list.
	 * @parameter adjacencyList Data structure to have information removed
	 * from.
	 * @parameter nameList Maps the string data to an integer.
	 * @parameter programInfo Contains the user specified vertices to remove
	 * from the adjacency list.
	 * @parameter useNameList Determines whether or not to use the nameList
	 * mapping.
	*/
	static void removeVertices(AdjacencyList &adjacencyList, const std::unordered_map<std::string, int> &nameListKey, 
								const std::vector<std::string> &programInfo, bool useNameList);

	/**
	 * Removes user specified edges from the adjacency list.
	 * @parameter adjacencyList Data structure to have information removed
	 * from.
	 * @parameter nameList Maps the string data to an integer.
	 * @parameter programInfo Contains the user specified edges to remove
	 * from the adjacency list.
	 * @parameter useNameList Determines whether or not to use the nameList
	 * mapping.
	*/
	static void removeEdges(AdjacencyList &adjacencyList, const std::unordered_map<std::string, int> &nameListKey, 
							const std::vector<std::string> &programInfo, bool useNameList);

	/**
	 * Takes the MST information and parses the path and query vertices.
	 * @parameter mstShortestPaths Contains the MST path information.
	 * @parameter MSTVertices Contains the MST query vertices.
	 * @parameter keyVertices Stores the path and query vertices.
	 * @parameter output An ofstream reference to print time measurements to a file.
	*/
	static void parseMSTResults(const std::vector<PathInformation> &mstShortestPaths, const std::vector<int> &MSTVertices, 
								std::vector<std::vector<int>> &keyVertices, std::ofstream &output);

	/**
	 * Takes the KSSP information and parses the paths.
	 * @parameter Stores the start/end vertex and path vertices.
	 * @parameter Contains the shortest paths.
	 * @parameter startVertex The start vertex.
	 * @parameter endVertex The end vertex.
	*/
	static void parseKSSPResults(std::vector<std::vector<int>> &keyVertices, const std::vector<PathInformation> &shortestPaths, 
								int startVertex, int endVertex);
};

#endif