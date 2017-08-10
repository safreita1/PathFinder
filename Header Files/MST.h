/*
 * MST.h
 *
 *  Created on: N/A
 *      Author: Scott Freitas
 */

#ifndef MST_H_
#define MST_H_

#include "PathInformation.h"
#include "AdjacencyList.h"
#include "DijkstrasAlgorithm.h"
#include "SearchSpaceReduction.h"
#include "CommunityIdentifier.h"
#include "GraphViz.h"
#include "Parsing.h"

#include <vector>
#include <thread>
#include <algorithm>
#include <set>
#include <fstream>
#include <unordered_map>
#include <chrono>

/**
 * This class finds a MST using shortest paths between a
 * set of user specified query nodes.
 */
class MST {
	
public:
	/**
	 * Runs the MST calculations, creates DOT and adjacency list of results.
	 * @parameter adjacencyList Contains the graph information.
	 * @parameter programInfo Contains arguements to program.
	 * @parameter output An ofstream reference to print time measurements to a file.
	 * @parameter debug If true, measure the run time of the program.
	 * @parameter nameListKey Creates a map between the string and integer 
	 * representation of the data.
	 * @parameter nameList Creates a map between the integer and string 
	 * representation of the data.
	 * @return int The status of the program calculations.
	 */
	static int runMST(const AdjacencyList &adjacencyList, std::vector<std::string> programInfo, std::ofstream &output, bool debug, 
				std::unordered_map<std::string, int> nameListKey, std::unordered_map<int, std::string> nameList);

	/**
	 * Creates a MST between a set of user specified query nodes.
	 * @parameter adjacencyList Contains the graph information.
	 * @parameter verticesToSearch The set of user specified query nodes 
	 * @parameter depthToSearch The depth to search for the first search space reduction (SSR1).
	 * @parameter debug If true, measure the run time of the program.
	 * @parameter numVerticesFirstIter Controls how many vertices are included in the 
	 * reduced adjacency list on the first depth level (SSR1).
	 * @parameter numVerticesSubsequentIter Controls how many vertices are included in 
	 * the reduced adjacency list on evey depth level except the first (SSR1).
	 * @parameter criticalVerticesNextIter Controls how many of the vertices in the 
	 * current iteration are carried into the next iteration (SSR1).
	 * @return PathInformation containing the MST between the query nodes.
	 * @parameter searchSpaceReduce Determines whether or not to use the search space
	 * reduction algorithm.
	 */
	static std::vector<PathInformation> calculateMST(const AdjacencyList &adjList, const std::vector<int> &verticesToSearch, 
														int depthToSearch, bool debug, int numVerticesFirstIter, int numVerticesSubsequentIter, 
														int criticalVerticesNextIter, std::ofstream &output, bool searchSpaceReduce);
private:
	/**
	 * The information needed for each thread.
	 */
	struct ThreadInfo {
		int startVertex;
		int endVertex;
		PathInformation pathInformation;
	};

	/**
	 * Sorts the path information based on path length.
	 */
	struct sort_func {
		bool operator()(const ThreadInfo &left, const ThreadInfo &right) {
			return left.pathInformation.getPathLength() < right.pathInformation.getPathLength();
		}
	};

	/**
	 * Removes any invalid paths.
	 */
	struct erase_func {
		bool operator()(const ThreadInfo &path) {
			return path.pathInformation.getPathLength() == 0;
		}
	};
};

#endif
