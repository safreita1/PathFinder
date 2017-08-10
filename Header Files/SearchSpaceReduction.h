/*
 * SearchSpaceReduction.h
 *
 *  Created on: Apr 23, 2016
 *      Author: scott
 */

#ifndef SEARCHSPACEREDUCTION_H_
#define SEARCHSPACEREDUCTION_H_

#include "PathInformation.h"
#include "AdjacencyList.h"
#include "Utility.h"

#include <algorithm>
#include <vector>

/**
 * This class creates a subset of the original graph
 * to reduce the search space and computation time of
 * the network connectivity algorithms.
 */
class SearchSpaceReduction {

public:
	/**
	 * Reduces the search space and computation time of
 	 * the network connectivity algorithms.
	 * @parameter adjacencyList The data structure containing all nodes and edges.
	 * @parameter reducedAdjacencyList This will the search space reduced adj. list
	 * containing the key nodes and edges.
	 * @parameter pathToSearch Contains the important vertices to search
	 * in the vicinity of.
	 * @parameter depthToSearch Determines how many "hops" or edge connections away 
	 * from a critial vertex to search.
	 * @parameter numVerticesFirstIter Controls how many vertices are included in the 
	 * reduced adjacency list on the first depth level.
	 * @parameter numVerticesSubsequentIter Controls how many vertices are included in 
	 * the reduced adjacency list on evey depth level except the first.
	 * @parameter criticalVerticesNextIter Controls how many of the vertices in the 
	 * current iteration are carried into the next iteration.
	 */
	static void searchSpaceReduce(const AdjacencyList &adjacencyList, AdjacencyList &reducedAdjacencyList, const PathInformation &pathToSearch, 
									int depthToSearch, int numVerticesFirstIter, int numVerticesSubsequentIter, int criticalVerticesNextIter);

	/**
	 * This function determines which vertices and edges are important
	 * in the graph.
	 * @parameter adjacencyList Contains the graph information.
	 * @parameter pathToSearch Contains the important vertices to search
	 * in the vicinity of.
	 * @parameter updatedAdjacencyList Contains the reduced adjacency list
	 * with all vertices and edges identified as 'key'.
	 * @parameter currentDepth The current depth that the program is at in
	 * the breadth first search of the network.
	 * @parameter averageCentrality The average degree centrality of the 
	 * network.
	 * @parameter numVerticesFirstIter Controls how many vertices are included in the 
	 * reduced adjacency list on the first depth level.
	 * @parameter numVerticesSubsequentIter Controls how many vertices are included in 
	 * the reduced adjacency list on evey depth level except the first.
	 * @parameter criticalVerticesNextIter Controls how many of the vertices in the 
	 * current iteration are carried into the next iteration.
	 * @parameter depthToSearch Determines how many "hops" or edge connections away 
	 * from a critial vertex to search.
	 */
	static void keyNeighboringVertices(const AdjacencyList &adjacencyList, const PathInformation &pathToSearch, 
											AdjacencyList &updatedAdjacencyList, int &currentDepth, int depthToSearch, 
											int averageCentrality, int numVerticesFirstIter, int numVerticesSubsequentIter, 
											int criticalVerticesNextIter);

private:
	/**
	 * Sorts the pairs.
	 */
	struct sort_func {
		bool operator()(const std::pair<int, int> &left, const std::pair<int, int> &right) {
			return left.second > right.second;
		}
	};
};

#endif
