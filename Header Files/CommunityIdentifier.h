/*
 * CommunityIdentifier.h
 *
 *  Created on: N/A
 *      Author: Scott Freitas
 */

#ifndef COMMUNITYIDENTIFIER_H_
#define COMMUNITYIDENTIFIER_H_

#include "AdjacencyList.h"
#include "PathInformation.h"
#include "SearchSpaceReduction.h"

#include <vector>

/**
 * This class creates an AdjacencyList containing a subset nodes
 * and edges from the adjacencylist. Nodes and edges are identified
 * the KNV heuristic.
 */
class CommunityIdentifier
{
public:
	/**
	 * This function creates a reduced AdjacencyList that contains a subset
	 * of nodes and edges from the adjacencyList.
	 * @parameter adjacencyList The data structure containing all nodes and edges.
	 * @parameter keyVertices Contains query vertices and path vertices.
	 * @parameter numVerticesFirstIter Controls how many vertices are included in the 
	 * reduced adjacency list on the first depth level.
	 * @parameter numVerticesSubsequentIter Controls how many vertices are included in 
	 * the reduced adjacency list on evey depth level except the first.
	 * @parameter criticalVerticesNextIter Controls how many of the vertices in the 
	 * current iteration are carried into the next iteration.
	 * @parameter depthToSearch Determines how many "hops" or edge connections away 
	 * from a critial vertex to search.
	 */
	static AdjacencyList identifyCommunities(const AdjacencyList &adjacencyList, const std::vector<std::vector<int>> 
												&keyVertices, int numVerticesFirstIter, int numVerticesSubsequentIter, 
												int criticalVerticesNextIter, int depthToSearch);
};

#endif
