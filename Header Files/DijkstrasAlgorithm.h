/*
 * DijkstrasAlgorithm.h
 *
 *  Created on: Jan 18, 2016
 *      Author: Scott Freitas
 */

#ifndef DIJKSTRASALGORITHM_H_
#define DIJKSTRASALGORITHM_H_

#include "PathInformation.h"
#include "AdjacencyList.h"

#include <mutex>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <unordered_map>
#include <utility>

class DijkstrasAlgorithm {

public:
	/**
	 * This function computes the shortest path from a start to end vertex.
	 * @parameter startVertex  The start point of the path to be calculated.
	 * @parameter endVertex  The end point of the path to be calculated.
	 * @parameter adjacencyList  An AdjacencyList that hold all the edges for each vertex.
	 * @parameter pathInfo  Shortest path information will be stored in here. 
	 * @parameter firstEdgeToDelete  This is the vertex for the first half of the edge to
	 * delete.
	 * @parameter secondEdgeToDelete  This is the vertex for the second half of the edge to
	 * delete.
	 * @parameter removeEdge  This value determines whether or not to remove the edge given
	 * by firstEdgeToDelte and secondEdgeToDelete.
	 */
	static void singleSourceShortestPath(int startVertex, int endVertex, AdjacencyList adjacencyList, PathInformation &pathInfo, 
													int firstEdgeToDelete, int secondEdgeToDelete, bool removeEdge);
};

#endif
