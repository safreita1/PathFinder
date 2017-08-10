/*
 * KSimpleShortestPaths.cpp
 *
 *  Created on: Jan 17, 2016
 *      Author: Scott Freitas
 */

#include "KSimpleShortestPaths.h"

int KSimpleShortestPaths::runKSSP(const AdjacencyList &adjacencyList, std::vector<std::string> programInfo, std::ofstream &output, 
									bool debug, std::unordered_map<std::string, int> nameListKey, std::unordered_map<int, std::string> 
									nameList, bool useKSSP) {

	//General program parameters
	AdjacencyList community;
	std::chrono::steady_clock::time_point startTime, endTime;
	bool useNameList = false;
	bool validPathFound = true;
	bool searchSpaceReduce = true;
	std::istringstream(programInfo.at(21)) >> std::boolalpha >> useNameList;
	std::istringstream(programInfo.at(42)) >> std::boolalpha >> searchSpaceReduce;
	std::string photoId = programInfo.at(20);
	std::vector<PathInformation> shortestPaths;
	std::vector<std::vector<int>> keyVertices(2);
	int startVertex = -1;
	int endVertex = -1;
	int numberOfPathsToCalc = stoi(programInfo.at(7));
	int exitCode = 1;

	//Search Space Reduction 1 Parameters
	int depthSSR1 = stoi(programInfo.at(8));
	int numVerticesFirstIteraionSSR1 = stoi(programInfo.at(9));
	int numVerticesSubsequentIterationsSSR1 = stoi(programInfo.at(10));
	int criticalVerticesNextIterationSSR1 = stoi(programInfo.at(11));

	//Search Space Reduction 2 Parameters
	int numVerticesFirstIteraionSSR2 = stoi(programInfo.at(12));
	int numVerticesSubsequentIterationsSSR2 = stoi(programInfo.at(13));
	int criticalVerticesNextIterationSSR2 = stoi(programInfo.at(14));
	int depthSSR2 = stoi(programInfo.at(15));

	//Community Identification Parameters
	int numVerticesFirstIteraionCI = stoi(programInfo.at(16));
	int numVerticesSubsequentIterationsCI = stoi(programInfo.at(17));
	int criticalVerticesNextIterationCI = stoi(programInfo.at(18));
	int depthCI = stoi(programInfo.at(19));

	//Visualization Parameters
	int colorSchemeFilter = stoi(programInfo.at(22));
	int edgeSchemeFilter = stoi(programInfo.at(29));
	std::string nodeSize = programInfo.at(23);

	//Path parameters
	std::string adjListLocation = "/path_finder_files/user_adj_lists/adjlist" + photoId  + ".txt";
	std::string dotFileLocation = "/path_finder_files/user_files/" + photoId + ".txt";
	std::string dotFileLocationDefaultFont = "/path_finder_files/user_files/" + photoId + "defaultfont.txt";

	//Check if a name dataset is being used
	if (useNameList) {
		//Check to see that the strings being searched for exist
		if (nameListKey.count(programInfo.at(2)) && nameListKey.count(programInfo.at(3))) {
			startVertex = nameListKey.at(programInfo.at(2));
			endVertex = nameListKey.at(programInfo.at(3));
		}
	}
	//Otherwis, it's an integer dataset
	else {
		startVertex = stoi(programInfo.at(2));
		endVertex = stoi(programInfo.at(3));
	}

	//Only find paths if the start and end vertices exist in the adj. list
	if (adjacencyList.validVertex(startVertex) && adjacencyList.validVertex(endVertex)) {

		shortestPaths.resize(numberOfPathsToCalc);

		//Start recording the time elapsed
		if (debug) {
			startTime = std::chrono::steady_clock::now();
		}

		//Uses the K-Simple Shortest Paths single thread, non-search reduced function
		if (useKSSP) {
			KSimpleShortestPaths::kSSP(startVertex, endVertex, numberOfPathsToCalc, adjacencyList, shortestPaths, 
										validPathFound, output, debug);
		}
		else {
		//Calls the K-Simple Shortest Paths multithreaded and search reduced function
		KSimpleShortestPaths::kSSPR(startVertex, endVertex, numberOfPathsToCalc, adjacencyList, depthSSR1, 
		   							debug, shortestPaths, validPathFound, numVerticesFirstIteraionSSR1,
		   							numVerticesSubsequentIterationsSSR1, criticalVerticesNextIterationSSR1, 
		  							numVerticesFirstIteraionSSR2, numVerticesSubsequentIterationsSSR2,
		  							criticalVerticesNextIterationSSR2, depthSSR2, output, searchSpaceReduce);
		}

		//End time
		if (debug) {
			endTime = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsedTime = endTime - startTime;
			output << "Time to run KSSPR: " << elapsedTime.count() << " seconds." << std::endl;
			output << std::endl;
		}

		//If a shortest path exists, graph it
		if (validPathFound) {

			//This checks the number of paths found in the algorithm and resizes the vector
			int pathsFound = 0;
			for (int index = 0; index < shortestPaths.size(); index++) {
				if (shortestPaths.at(index).getPathLength() > 0) {
					pathsFound++;
				}
			}
			shortestPaths.resize(pathsFound);
			
			//Get start/end vertices and the path vertices and store them as key vertices
			Parsing::parseKSSPResults(keyVertices, shortestPaths, startVertex, endVertex);

			//Start recording the time elapsed
			if (debug) {
				startTime = std::chrono::steady_clock::now();
			}

			//Identify the communities on the shortest paths
			community = CommunityIdentifier::identifyCommunities(adjacencyList, keyVertices, numVerticesFirstIteraionCI, 
																	numVerticesSubsequentIterationsCI, 
																	criticalVerticesNextIterationCI, depthCI);			
			//End time
			if (debug) {
				endTime = std::chrono::steady_clock::now();
				std::chrono::duration<double> elapsedTime = endTime - startTime;
				output << "Time to complete community identification: " << elapsedTime.count() << " seconds." << std::endl;
				output << std::endl;
			}

			//Start recording the time elapsed
			if (debug) {
				startTime = std::chrono::steady_clock::now();
			}

			//Create a DOT and adjacency list file
			GraphViz::convertKSSPAdjListToDOT(adjacencyList, community, keyVertices, shortestPaths, nameList, useNameList, 
												colorSchemeFilter, nodeSize, edgeSchemeFilter, dotFileLocation, 
												dotFileLocationDefaultFont, adjListLocation);

			//End time
			if (debug) {
				endTime = std::chrono::steady_clock::now();
				std::chrono::duration<double> elapsedTime = endTime - startTime;
				output << "Time to convert to DOT format: " << elapsedTime.count() << " seconds." << std::endl;
				output << std::endl;
			}

			//Program has exited successfully
			exitCode = 0;
		}
		else {
			//No paths found
			exitCode = 2;
		}
	}
	else {
		//Vertices don't exist in adj. list
		exitCode = 2;
	}

	return exitCode;
}

void KSimpleShortestPaths::kSSP(int startVertex, int endVertex, int numberOfPathsToCalc, AdjacencyList adjacencyList, 
								std::vector<PathInformation> &kShortestPaths, bool &validPathFound, std::ofstream &output,
								bool debug) {
	int currentPathCount = 0;
	bool endFlag = false;

	//Get shortest path
	PathInformation firstPath = PathInformation();
	DijkstrasAlgorithm::singleSourceShortestPath(startVertex, endVertex, adjacencyList, firstPath, 0, 0, false);

	//Check to see if a path was found, if not, exit
	if (firstPath.getPathLength() == 0) {
		validPathFound = false;
		return;
	}

	//Put information into array
	kShortestPaths[currentPathCount].setPathLength(firstPath.getPathLength());
	kShortestPaths[currentPathCount].setPath(firstPath.getPath());

	//Compute the shortest path k times
	while(currentPathCount < numberOfPathsToCalc - 1 && !endFlag) {
		//Create a variable to hold the shortest path for each iteration
		PathInformation nextShortestPath = PathInformation();
		int firstEdgeToDelete = -1;
		int secondEdgeToDelete = -1;

		//Remove each edge in the current shortest path
		for(int index = 0; index < kShortestPaths[currentPathCount].getPathLength(); index++) {
			//Get the edge's vertices
			int firstVertex = kShortestPaths[currentPathCount].getPathAt(index);
			int secondVertex = kShortestPaths[currentPathCount].getPathAt(index + 1);

			//Remove the link(edge)
			adjacencyList.removeEdge(firstVertex, secondVertex);

			PathInformation currentPath = PathInformation();
			DijkstrasAlgorithm::singleSourceShortestPath(startVertex, endVertex, adjacencyList, currentPath, 0, 0, false);

			//Add link back(edge)
			adjacencyList.addEdge(firstVertex, secondVertex);

			//If the deleted link created the next shortest path update the variables	
			if (nextShortestPath.getPathLength() == 0) {
				if (currentPath.getPathLength() > 0) {

					nextShortestPath.setPath(currentPath.getPath());
					nextShortestPath.setPathLength(currentPath.getPathLength());

					firstEdgeToDelete = firstVertex;
					secondEdgeToDelete = secondVertex;
				}
			}
			else if (currentPath.getPathLength() < nextShortestPath.getPathLength()){

				nextShortestPath.setPath(currentPath.getPath());
				nextShortestPath.setPathLength(currentPath.getPathLength());

				firstEdgeToDelete = firstVertex;
				secondEdgeToDelete = secondVertex;
			}
		}


		//Add the next shortest path to the array if there's more than one path to calculate
		//Check to make sure that the newest shortest shortest path does not equal a previous path
		if(nextShortestPath.getPathLength() > 0) {
			currentPathCount++;
			kShortestPaths[currentPathCount].setPath(nextShortestPath.getPath());
			kShortestPaths[currentPathCount].setPathLength(nextShortestPath.getPathLength());

			//Remove the next shortest path link(edge) from the adjacency list
			adjacencyList.removeEdge(firstEdgeToDelete, secondEdgeToDelete);
		}

		//There are no more shortest paths, end the program.
		else {
			endFlag = true;
		}

	}

	if (debug) {
		currentPathCount = currentPathCount + 1;
		output << "Found " << currentPathCount << " paths." << std::endl << std::endl;
		//Print information on KSSP
		double avgPathLength = 0;
		for (int index = 0; index < currentPathCount; index++) {
			output << "Path: " << kShortestPaths[index].toString() << std::endl;
			avgPathLength += (double)kShortestPaths[index].getPathLength();
		}
		output << "Average path length: " << (double)(avgPathLength / currentPathCount) << std::endl << std::endl;
	}
}		

void KSimpleShortestPaths::kSSPR(int startVertex, int endVertex, int numberOfPathsToCalc, AdjacencyList adjacencyList, 
									int depthToSearch, bool debug, std::vector<PathInformation> &kShortestPaths, 
									bool &validPathFound, int numVerticesFirstIter, int numVerticesSubsequentIter, 
									int criticalVerticesNextIter, int numVerticesFirstIter2, int numVerticesSubsequentIter2, 
									int criticalVerticesNextIter2, int depth2, std::ofstream &output, bool searchSpaceReduce) {

	if (searchSpaceReduce) {
		AdjacencyList reducedAdjList1 = AdjacencyList(adjacencyList.size());
		AdjacencyList reducedAdjList2 = AdjacencyList(adjacencyList.size());
	}
	//Create the reduced search space adjacency lists
	AdjacencyList reducedAdjList1 = AdjacencyList(adjacencyList.size());
	AdjacencyList reducedAdjList2 = AdjacencyList(adjacencyList.size());
	PathInformation startEndVertices = PathInformation();
	
	std::chrono::steady_clock::time_point startTime, endTime;
	bool noMorePaths = false;	
	int currentPathCount = 0;
	std::vector<int> list1 = {startVertex, endVertex};
	startEndVertices.setPath(list1);
	startEndVertices.setPathLength(list1.size() - 1);

	//Start recording the time elapsed
	if (debug) {
		startTime = std::chrono::steady_clock::now();
	}

	//Check to see if a search space reduction is used
	if (searchSpaceReduce) {
		SearchSpaceReduction::searchSpaceReduce(adjacencyList, reducedAdjList1, startEndVertices, depthToSearch, numVerticesFirstIter, 
												numVerticesSubsequentIter, criticalVerticesNextIter);
	}

	//End time
	if (debug) {
		endTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsedTime = endTime - startTime;
		output << "Time to complete SSR1: " << elapsedTime.count() << " seconds." << std::endl;
		output << std::endl;
	}										

	//Start recording the time elapsed
	if (debug) {
		startTime = std::chrono::steady_clock::now();
	}

	PathInformation firstPath = PathInformation();

	//If searchSpaceReduce is true, use search space reduced graph
	if (searchSpaceReduce) {
		DijkstrasAlgorithm::singleSourceShortestPath(startVertex, endVertex, reducedAdjList1, firstPath, 0, 0, false);		
	}
	else {
		DijkstrasAlgorithm::singleSourceShortestPath(startVertex, endVertex, adjacencyList, firstPath, 0, 0, false);
	}


	//Put information into array
	kShortestPaths[currentPathCount].setPathLength(firstPath.getPathLength());
	kShortestPaths[currentPathCount].setPath(firstPath.getPath());

	//End time
	if (debug) {
		endTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsedTime = endTime - startTime;
		output << "Time to complete the first shortest path: " << elapsedTime.count() << " seconds." << std::endl;
		output << std::endl;
	}

	//Check to see if a path was found, if not, exit
	if (firstPath.getPathLength() == 0) {
		output << "There is no path between the two specified nodes" << std::endl;
		validPathFound = false;
		return;
	}	

	//Start recording the time elapsed
	if (debug) {
		startTime = std::chrono::steady_clock::now();
	}

	//Do a search space reduction if set
	if (searchSpaceReduce) {
		//Create a reduced adjacency list for the k - 1 shortest paths based on the 1st shortset path
		SearchSpaceReduction::searchSpaceReduce(adjacencyList, reducedAdjList2, firstPath, depth2, numVerticesFirstIter2, 
												numVerticesSubsequentIter2, criticalVerticesNextIter2);		
	}

	//End time
	if (debug) {
		endTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsedTime = endTime - startTime;
		output << "Time to complete the SSR2: " << elapsedTime.count() << " seconds." << std::endl;
		output << std::endl;
	}

	//Start recording the time elapsed
	if (debug) {
		startTime = std::chrono::steady_clock::now();
	}

	//Compute the shortest path k times
	while (currentPathCount < numberOfPathsToCalc - 1 && !noMorePaths) {
		//Create array of boost threads to run each dijkstras algorithm function
		std::vector<std::thread> threadPool;
		bool terminate = false;

		//Create array of structs to store information on the current shortest paths
		std::vector<ThreadInfo> threadInfo;
		threadInfo.resize(kShortestPaths[currentPathCount].getPathLength() + 1);

		//Initialize the array of structs
		for (int index = 0; index < kShortestPaths[currentPathCount].getPathLength(); index++) {
			threadInfo[index].firstVertex = kShortestPaths[currentPathCount].getPathAt(index);
			threadInfo[index].secondVertex = kShortestPaths[currentPathCount].getPathAt(index + 1);
			threadInfo[index].pathInformation = PathInformation();
		}
		
		//Use the search space reduced graph
		if (searchSpaceReduce) {
			//Start all of the threads
			for (int threadIndex = 0; threadIndex < kShortestPaths[currentPathCount].getPathLength(); threadIndex++) {
				threadPool.push_back(std::thread(DijkstrasAlgorithm::singleSourceShortestPath, startVertex, endVertex, 
										reducedAdjList2, std::ref(threadInfo[threadIndex].pathInformation), threadInfo[threadIndex].firstVertex, 
										threadInfo[threadIndex].secondVertex, true));
			}
		}
		//Otherwise use the non-search space reduced graph
		else {
			for (int threadIndex = 0; threadIndex < kShortestPaths[currentPathCount].getPathLength(); threadIndex++) {
				threadPool.push_back(std::thread(DijkstrasAlgorithm::singleSourceShortestPath, startVertex, endVertex, 
										adjacencyList, std::ref(threadInfo[threadIndex].pathInformation), threadInfo[threadIndex].firstVertex, 
										threadInfo[threadIndex].secondVertex, true));

			}
		}

		//Join the threads
		for (int threadIndex = 0; threadIndex < kShortestPaths[currentPathCount].getPathLength(); threadIndex++) {
			threadPool.at(threadIndex).join();
		}

		int shortestPathIndex = 0;
		//Search array of threadInfos for shortest path
		for (int threadIndex = 1; threadIndex < kShortestPaths[currentPathCount].getPathLength(); threadIndex++) {
			//Enter if the current path length is 0
			if (threadInfo[shortestPathIndex].pathInformation.getPathLength() == 0) {
				//If the next shortest path has a path length greater than 0, update the shortest path index
				if (threadInfo[threadIndex].pathInformation.getPathLength() > 0) {
					shortestPathIndex = threadIndex;
				}
			}
			//Current shortest path has a path length greater than 0
			else {
				//If the next path is shorter than the current path and the next path is not 0, update the shortest path index
				if (threadInfo[threadIndex].pathInformation.getPathLength() < threadInfo[shortestPathIndex].pathInformation.getPathLength() 
					&& threadInfo[threadIndex].pathInformation.getPathLength() > 0) {

					shortestPathIndex = threadIndex;
				}
			}
		}

		//Check condition of no more paths to be found
		if (threadInfo[shortestPathIndex].pathInformation.getPathLength() == 0) {
			noMorePaths = true;
		}

		else {
			//Set the shortest path and delete the edge that created the shortest path
			currentPathCount++;
			kShortestPaths[currentPathCount].setPath(threadInfo[shortestPathIndex].pathInformation.getPath());
			kShortestPaths[currentPathCount].setPathLength(threadInfo[shortestPathIndex].pathInformation.getPathLength());
			//If true, remove from search space reduced graph
			if (searchSpaceReduce) {
				reducedAdjList2.removeEdge(threadInfo[shortestPathIndex].firstVertex, threadInfo[shortestPathIndex].secondVertex);				
			}
			else {
				adjacencyList.removeEdge(threadInfo[shortestPathIndex].firstVertex, threadInfo[shortestPathIndex].secondVertex);
			}
			
		}
	}

	//End time
	if (debug) {
		endTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsedTime = endTime - startTime;
		output << "Time to run the k - 1 shortest paths: " << elapsedTime.count() << " seconds." << std::endl;
		output << std::endl;

		currentPathCount = currentPathCount + 1;
		output << "Found " << currentPathCount << " path(s)." << std::endl;
		//Print information on KSSP
		double avgPathLength = 0;
		for (int index = 0; index < currentPathCount; index++) {
			output << "Path: " << kShortestPaths[index].toString() << std::endl;
			//output << "Path " << index << ": " << kShortestPaths[index].toString() << std::endl;
			//output << "Length of path " << index << ": " << kShortestPaths[index].getPathLength() << std::endl;
			avgPathLength += (double)kShortestPaths[index].getPathLength();
		}
		output << "Average path length: " << (double)(avgPathLength / currentPathCount) << std::endl << std::endl;
	}
}








