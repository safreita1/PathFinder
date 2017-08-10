/*
 * GraphViz.h
 *
 *  Created on: N/A
 *      Author: Scott Freitas
 */

#ifndef GRAPHVIZ_H_
#define GRAPHVIZ_H_
#define _CRT_SECURE_NO_WARNINGS

#include "PathInformation.h"
#include "AdjacencyList.h"
#include "Utility.h"

#include <utility>
#include <vector>
#include <ctime>
#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>
#include <algorithm>

/**
 * This class creates a DOT and adjacency list file that
 * contains information on the nodes and edges used to create
 * the visualizations.
 */
class GraphViz
{

public:
	/**
	 * Creates a DOT and adjacency list file for the KSSP algorithm. This
	 * sets all visualization paramters.
	 * @parameter nonSearchReducedAdjList  This adj. list contains
	 * all the orginal edges and vertices from the dataset.
	 * @parameter adjList Reduced adj. list containing all the nodes
	 * and edges to be visualized.
	 * @parameter keyVertices Contains the query and path vertices.
	 * @parameter shortestPaths Contains the shortest paths.
	 * @parameter nameList Contains the mapping from integer to name.
	 * @parameter useNameList Determines whether or not to map an integer
	 * to a name.
	 * @parameter colorSchemeFilter Determines which vertex color scheme to use.
	 * @parameter nodeSize Determines the vertex size
	 * @parameter edgeSchemeFilter Determines whether the edges are gray or colored.
	 * @parameter dotFileLocation The path to save the DOT file.
	 * @parameter dotFileLocationDefaultFont The path to save the second DOT file.
	 * @parameter adjListLocation The path to save the adjacency list.
	 */
	static void convertKSSPAdjListToDOT(const AdjacencyList &nonSearchReducedAdjList, const AdjacencyList &adjList, 
										const std::vector<std::vector<int>> &keyVertices, const std::vector<PathInformation> 
										&shortestPaths, const std::unordered_map<int, std::string> &nameList, bool useNameList, 
										int colorSchemeFilter, std::string nodeSize, int edgeSchemeFilter, std::string dotFileLocation, 
										std::string dotFileLocationDefaultFont, std::string adjListLocation);

	/**
	 * Creates a DOT and adjacency list file for the MST algorithm. This
	 * sets all visualization paramters.
	 * @parameter nonSearchReducedAdjList  This adj. list contains
	 * all the orginal edges and vertices from the dataset.
	 * @parameter adjList Reduced adj. list containing all the nodes
	 * and edges to be visualized.
	 * @parameter keyVertices Contains the query and path vertices.
	 * @parameter shortestPaths Contains the shortest paths.
	 * @parameter nameList Contains the mapping from integer to name.
	 * @parameter useNameList Determines whether or not to map an integer
	 * to a name.
	 * @parameter colorSchemeFilter Determines which vertex color scheme to use.
	 * @parameter nodeSize Determines the vertex size
	 * @parameter edgeSchemeFilter Determines whether the edges are gray or colored.
	 * @parameter dotFileLocation The path to save the DOT file.
	 * @parameter dotFileLocationDefaultFont The path to save the second DOT file.
	 * @parameter adjListLocation The path to save the adjacency list.
	 */
	static void convertMSTAdjListToDOT(const AdjacencyList &nonSearchReducedAdjList, const AdjacencyList &adjList, 
										const std::vector<std::vector<int>> &keyVertices, const std::vector<PathInformation> 
										&shortestPaths, const std::unordered_map<int, std::string> &nameList, bool useNameList, 
										int colorSchemeFilter, std::string nodeSize, int edgeSchemeFilter, std::string dotFileLocation, 
										std::string dotFileLocationDefaultFont, std::string adjListLocation);

private:
	/**
	 * Determines which vertices to include in the DOT and adj. list files.
	 * Controls the color scheme and size of each vertex.
	 * @parameter nonSearchReducedAdjList  This adj. list contains
	 * all the orginal edges and vertices from the dataset.
	 * @parameter adjListCopy A copy of the original adjacencyList 
	 * containing all the vertices and edges from the dataset.
	 * @parameter keyVertices Contains the query and path vertices.	
	 * @parameter graphInput String containing the DOT information.
	 * @parameter nameList Contains the mapping from integer to name.
	 * @parameter useNameList Determines whether or not to map an integer
	 * to a name.
	 * @parameter colorScheme This is the color scheme for each vertex.
	 * @parameter nodeSize Determines the vertex size
	 */
	static void graphVertices(const AdjacencyList &nonSearchReducedAdjList, AdjacencyList &adjListCopy, 
								const std::vector<std::vector<int>> &keyVertices, std::string &graphInput, 
								const std::unordered_map<int, std::string> &nameList, bool useNameList, 
								std::vector<std::string> colorScheme, std::string nodeSize);
		
	/**
	 * Determines which edges to include in the DOT and adj. list files. This
	 * is only for gray edges.
	 * @parameter adjListCopy A copy of the original adjacencyList 
	 * @parameter keyVertices Contains the query and path vertices.
	 * @parameter shortestPaths Contains the shortest paths.	
	 * @parameter graphInput String containing the DOT information.
	 * @parameter firstEdgeSet Contains the vertices that make up the first half
	 * of an edge. Used to make the adj. list file.
	 * @parameter secondEdgeSet Contains the vertices that make up the second half
	 * of an edge. Used to make the adj. list file.
	 * @parameter NumberOfUniqueVertices The number of unique vertices. Used to
	 * make the adj. list file.
	 * @parameter nameList Contains the mapping from integer to name.
	 * @parameter useNameList Determines whether or not to map an integer
	 * to a name.
	 */
	static void graphEdges(AdjacencyList &adjListCopy, const std::vector<std::vector<int>> &keyVertices, 
							const std::vector<PathInformation> &shortestPaths, std::string &graphInput, 
							std::vector<int> &firstEdgeSet, std::vector<int> &secondEdgeSet, std::set<int> 
							&numberOfUniqueVertices, bool useNameList, const std::unordered_map<int, std::string> &nameList);

	/**
	 * Determines which edges to include in the DOT and adj. list files. This
	 * is only for colored edges.
	 * @parameter adjListCopy A copy of the original adjacencyList 
	 * @parameter keyVertices Contains the query and path vertices.
	 * @parameter shortestPaths Contains the shortest paths.	
	 * @parameter colorScheme This is the color scheme for each edge.
	 * @parameter graphInput String containing the DOT information.
	 * @parameter firstEdgeSet Contains the vertices that make up the first half
	 * of an edge. Used to make the adj. list file.
	 * @parameter secondEdgeSet Contains the vertices that make up the second half
	 * of an edge. Used to make the adj. list file.
	 * @parameter NumberOfUniqueVertices The number of unique vertices. Used to
	 * make the adj. list file.
	 * @parameter nameList Contains the mapping from integer to name.
	 * @parameter useNameList Determines whether or not to map an integer
	 * to a name.
	 */
	static void graphEdgesColored(AdjacencyList &adjListCopy, const std::vector<std::vector<int>> &keyVertices, 
									const std::vector<PathInformation> &shortestPaths, std::string &graphInput, 
									std::vector<std::string> colorScheme, std::vector<int> &firstEdgeSet, 
									std::vector<int> &secondEdgeSet, std::set<int> &numberOfUniqueVertices, bool useNameList, 
									const std::unordered_map<int, std::string> &nameList);

	/**
	 * Saves the DOT information to a file.
	 * @parameter graphInput String containing the DOT information.
	 * @parameter nodeSize Determines the vertex size
	 * @parameter dotFileLocation The path to save the DOT file.
	 * @parameter dotFileLocationDefaultFont The path to save the second DOT file.
	 */
	static void saveDOTFile(std::string graphInput, std::string nodeSize, std::string dotFileLocation, 
							std::string dotFileLocationDefaultFont);

	/**
	 * Saves the information used to create the DOT file in adj. list
	 * format to a file.
	 * @parameter numberO
	 * @parameter firstEdgeSet Contains the vertices that make up the first half
	 * of an edge. Used to make the adj. list file.
	 * @parameter secondEdgeSet Contains the vertices that make up the second half
	 * of an edge. Used to make the adj. list file.
	 * @parameter NumberOfUniqueVertices The number of unique vertices. Used to
	 * make the adj. list file.
	 * @parameter nameList Contains the mapping from integer to name.
	 * @parameter useNameList Determines whether or not to map an integer
	 * to a name.
	 */
	static void saveAdjListFile(std::string adjListLocation, std::vector<int> &firstEdgeSet, 
								std::vector<int> &secondEdgeSet, std::set<int> &numberOfUniqueVertices, 
								const std::unordered_map<int, std::string> &nameList, bool useNameList);
};

#endif