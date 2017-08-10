/*
 * KSimpleShortestPaths.h
 *
 *  Created on: Jan 23, 2016
 *      Author: Scott Freitas
 */

#ifndef KSIMPLESHORTESTPATHS_H_
#define KSIMPLESHORTESTPATHS_H_

#include "PathInformation.h"
#include "DijkstrasAlgorithm.h"
#include "AdjacencyList.h"
#include "SearchSpaceReduction.h"
#include "CommunityIdentifier.h"
#include "GraphViz.h"
#include "Parsing.h"

#include <thread>
#include <vector>
#include <limits>
#include <atomic>
#include <fstream>
#include <chrono>

/**
 * This class finds the paths from one vertex to another.
 * There exits both a single threaded and multi-threaded
 * variation.
 */
class KSimpleShortestPaths {

public:
	/**
	 * Runs the KSSP calculations, creates DOT and adjacency list of results.
	 * @parameter adjacencyList Contains the graph information.
	 * @parameter programInfo Contains arguements to program.
	 * @parameter output An ofstream reference to print time measurements to a file.
	 * @parameter debug If true, measure the run time of the program.
	 * @parameter nameListKey Creates a map between the string and integer 
	 * representation of the data.
	 * @parameter nameList Creates a map between the integer and string 
	 * representation of the data.
	 * @parameter useKSSP Determines whether or not to use single threaded non-search 
	 * reduced version of KSSP or multithreaded search reduced version.
	 * @return int The status of the program calculations.
	 */
	static int runKSSP(const AdjacencyList &adjacencyList, std::vector<std::string> programInfo, std::ofstream &output, 
									bool debug, std::unordered_map<std::string, int> nameListKey, 
									std::unordered_map<int, std::string> nameList, bool useKSSP);

	/**
	 * Computes the K-Simple Shortest Paths in single threaded mode.
	 * @parameter startVertex  This is the start of the path that all calculations will originate.
	 * @parameter endVertex  This is the end destination that all paths will converge to.
	 * @parameter numberOfPathsToCalc  This is the number of paths to calculate.
	 * @parameter adjacencyList  Contains the graph information.
	 * @parameter kShortestPaths Contains the information for each shortest path found.
	 * @parameter validPathFound True if a path was found, false otherwise.
	 * @parameter output An ofstream reference to print time measurements to a file.
	 * @parameter debug If true, measure the run time of the program.
	 */
	static void kSSP(int startVertex, int endVertex, int numberOfPathsToCalc, AdjacencyList adjacencyList, 
						std::vector<PathInformation> &kShortestPaths, bool &validPathFound, std::ofstream &output,
						bool debug);

	/**
	 * Computes the K-Simple Shortest Paths in multi-threaded mode.
	 * @parameter startVertex  This is the start of the path that all calculations will originate.
	 * @parameter endVertex  This is the end destination that all paths will converge to.
	 * @parameter numberOfPathsToCalc  This is the number of paths to calculate.
	 * @parameter adjacencyList  Contains the graph information.
	 * @parameter depthToSearch The depth to search for the first search space reduction (SSR1).
	 * @parameter debug If true, measure the run time of the program.
	 * @parameter kShortestPaths Contains the information for each shortest path found.
	 * @parameter validPathFound True if a path was found, false otherwise.
	 * @parameter numVerticesFirstIter Controls how many vertices are included in the 
	 * reduced adjacency list on the first depth level (SSR1).
	 * @parameter numVerticesSubsequentIter Controls how many vertices are included in 
	 * the reduced adjacency list on evey depth level except the first (SSR1).
	 * @parameter criticalVerticesNextIter Controls how many of the vertices in the 
	 * current iteration are carried into the next iteration (SSR1).
	 * @parameter numVerticesFirstIter2 Controls how many vertices are included in the 
	 * reduced adjacency list on the first depth level (SSR2).
	 * @parameter numVerticesSubsequentIter2 Controls how many vertices are included in 
	 * the reduced adjacency list on evey depth level except the first (SSR2).
	 * @parameter criticalVerticesNextIter2 Controls how many of the vertices in the 
	 * current iteration are carried into the next iteration (SSR2).
	 * @parameter depthSSR2 The depth to search for the first search space reduction (SSR2).
	 * @parameter output An ofstream reference to print time measurements to a file.
	 * @parameter searchSpaceReduce Determines whether or not to use the search space
	 * reduction algorithm.
	 */
	static void kSSPR(int startVertex, int endVertex, int numberOfPathsToCalc, AdjacencyList adjacencyList, 
						int depthToSearch, bool debug, std::vector<PathInformation> &kShortestPaths, 
						bool &validPathFound, int numVerticesFirstIter, int numVerticesSubsequentIter, 
						int criticalVerticesNextIter, int numVerticesFirstIter2, int numVerticesSubsequentIter2, 
						int criticalVerticesNextIter2, int depthSSR2, std::ofstream &output, bool searchSpaceReduce);

private:
	/**
	 * Stores information used for each parallel single source shortest path computation 
	 */
	struct ThreadInfo {
		int firstVertex;
		int secondVertex;
		PathInformation pathInformation;
	};
};

#endif 
