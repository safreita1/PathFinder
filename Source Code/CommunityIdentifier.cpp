/*
 * CommunityIdentifier.h
 *
 *  Created on: N/A
 *      Author: Scott Freitas
 */

#include "CommunityIdentifier.h"


AdjacencyList CommunityIdentifier::identifyCommunities(const AdjacencyList &adjacencyList, const std::vector<std::vector<int>> 
														&keyVertices, int numVerticesFirstIter, int numVerticesSubsequentIter, 
														int criticalVerticesNextIter, int depthToSearch) {
	
	AdjacencyList communityList = AdjacencyList(adjacencyList.size(), adjacencyList.vertexCount());

	PathInformation pathList = PathInformation();
	std::vector<int> combinedVertexList;

	//Combine the keyVertices into one vertex
	combinedVertexList.insert(combinedVertexList.end(), keyVertices[0].begin(), keyVertices[0].end());
	combinedVertexList.insert(combinedVertexList.end(), keyVertices[1].begin(), keyVertices[1].end());

	//Create a combined 'path' to run the DFS and heuristics on
	pathList.setPath(combinedVertexList);
	pathList.setPathLength(combinedVertexList.size() - 1);


	//Reduce the graph size based on a vertex centrality heuristic
	if (depthToSearch > 0) {
		SearchSpaceReduction::searchSpaceReduce(adjacencyList, communityList, pathList, depthToSearch, numVerticesFirstIter, 
												numVerticesSubsequentIter, criticalVerticesNextIter);
	}

	return communityList;
}
