/*
 * MST.cpp
 *
 *  Created on: N/A
 *      Author: Scott Freitas
 */

#include "MST.h"

int MST::runMST(const AdjacencyList &adjacencyList, std::vector<std::string> programInfo, std::ofstream &output, bool debug, 
				std::unordered_map<std::string, int> nameListKey, std::unordered_map<int, std::string> nameList) {

	//General program parameters
	AdjacencyList community;
	std::chrono::steady_clock::time_point startTime, endTime;
	std::vector<PathInformation> mstShortestPaths;
	std::vector<int> MSTVertices;
	std::vector<std::vector<int>> keyVertices(2);	
	bool validMSTVertices = true;
	bool useNameList = false;
	bool searchSpaceReduce = true;
	std::istringstream(programInfo.at(21)) >> std::boolalpha >> useNameList;		
	std::istringstream(programInfo.at(42)) >> std::boolalpha >> searchSpaceReduce;
	std::string instruction = programInfo.at(1);
	std::string photoId = programInfo.at(20);
	int exitCode = 1;

	//Search Space Reduction 1 Parameters
	int depthSSR1 = stoi(programInfo.at(8));
	int numVerticesFirstIterationSSR1MST = stoi(programInfo.at(30));
	int numVerticesSubsequentIterationsSSR1MST = stoi(programInfo.at(31));
	int criticalVerticesNextIterationSSR1MST = stoi(programInfo.at(32));

	//Community Identification Parameters
	int numVerticesFirstIterationCIMST = stoi(programInfo.at(33));
	int numVerticesSubsequentIterationsCIMST = stoi(programInfo.at(34));
	int criticalVerticesNextIterationCIMST = stoi(programInfo.at(35));
	int depthCIMST = stoi(programInfo.at(36));

	//Visualization Parameters
	int colorSchemeFilter = stoi(programInfo.at(22));
	int edgeSchemeFilter = stoi(programInfo.at(29));
	std::string nodeSize = programInfo.at(23);

	//Path parameters
	char pathToExe[] = "/path_finder_files/programs/GraphViz.exe";
	std::string adjListLocation = "/path_finder_files/user_adj_lists/adjlist" + photoId  + ".txt";
	std::string dotFileLocation = "/path_finder_files/user_files/" + photoId + ".txt";
	std::string dotFileLocationDefaultFont = "/path_finder_files/user_files/" + photoId + "defaultfont.txt";

	//Add the MST vertices that are to be searched for
	for (int index = 2; index < 7; index++) {
		if (useNameList) {
			if (nameListKey.count(programInfo.at(index))) {
				//If the mst vertex exists, add it to the list
				if (adjacencyList.validVertex(nameListKey.at(programInfo.at(index)))) {
					MSTVertices.push_back(nameListKey.at(programInfo.at(index)));
				}
			}
		}
		else if(stoi(programInfo.at(index)) != -1){
			//If the mst vertex exists, add it to the list
			if (adjacencyList.validVertex(stoi(programInfo.at(index)))) {
				MSTVertices.push_back(stoi(programInfo.at(index)));
			}
		}
	}

	//Only search for a tree if there are at least valid 2 vertices in the list
	if (MSTVertices.size() > 1) {

		//Start recording the time elapsed
		if (debug) {
			startTime = std::chrono::steady_clock::now();
		}
		
		//Calculate the MST
		mstShortestPaths = MST::calculateMST(adjacencyList, MSTVertices, depthSSR1, debug, numVerticesFirstIterationSSR1MST, 
												numVerticesSubsequentIterationsSSR1MST, criticalVerticesNextIterationSSR1MST, output,
												searchSpaceReduce);

		//End time
		if (debug) {
			endTime = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsedTime = endTime - startTime;
			output << "Time run MST: " << elapsedTime.count() << " seconds." << std::endl;
			output << std::endl;
		}
	}

	//Enter if an MST is found
	if (mstShortestPaths.size() > 0) {		
		
		//Get the user defined start vertices and the resulting MST vertices from the calcuation and store them in the keyVertices
		Parsing::parseMSTResults(mstShortestPaths, MSTVertices, keyVertices, output);

		//Start recording the time elapsed
		if (debug) {
			startTime = std::chrono::steady_clock::now();
		}

		//Identify communities
		community = CommunityIdentifier::identifyCommunities(adjacencyList, keyVertices, numVerticesFirstIterationCIMST, 
																numVerticesSubsequentIterationsCIMST, criticalVerticesNextIterationCIMST, 
																depthCIMST);

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
		GraphViz::convertMSTAdjListToDOT(adjacencyList, community, keyVertices, mstShortestPaths, nameList, useNameList, 
											colorSchemeFilter, nodeSize, edgeSchemeFilter, dotFileLocation, dotFileLocationDefaultFont, 
											adjListLocation);

		//End time
		if (debug) {
			endTime = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsedTime = endTime - startTime;
			output << "Time to convert to DOT format: " << elapsedTime.count() << " seconds." << std::endl;
			output << std::endl;
		}

		//Program has executed successfully
		exitCode = 0;
	}
	else {
		//No paths found
		exitCode = 2;
	}

	return exitCode;
}

std::vector<PathInformation> MST::calculateMST(const AdjacencyList &adjacencyList, const std::vector<int> &verticesToSearch, 
												int depthToSearch, bool debug, int numVerticesFirstIter, int numVerticesSubsequentIter, 
												int criticalVerticesNextIter, std::ofstream &output, bool searchSpaceReduce) {

	//Create the reduced search space adjacency lists
	AdjacencyList reducedAdjList1 = AdjacencyList(adjacencyList.size());
	std::set<int> verticesFound;

	//Create array of structs to store information on the current shortest paths
	std::vector<ThreadInfo> pathsToSearch;
	int pathCount = 0;

	std::vector <PathInformation> shortestPaths;

	//Initialize the array of paths
	for (int index = 0; index < verticesToSearch.size(); index++) {
		for (int innerIndex = 1 + index; innerIndex < verticesToSearch.size(); innerIndex++) {
			pathsToSearch.push_back(ThreadInfo());
			pathsToSearch.at(pathCount).startVertex = verticesToSearch.at(index);
			pathsToSearch.at(pathCount).endVertex = verticesToSearch.at(innerIndex);
			pathsToSearch.at(pathCount).pathInformation = PathInformation();

			pathCount++;
		}
	}

	PathInformation tempPath = PathInformation();
	tempPath.setPath(verticesToSearch);
	tempPath.setPathLength(verticesToSearch.size() - 1);
	
	//Search space reduce the adjacency list
	if (searchSpaceReduce) {
		SearchSpaceReduction::searchSpaceReduce(adjacencyList, reducedAdjList1, tempPath, depthToSearch, 
			numVerticesFirstIter, numVerticesSubsequentIter, criticalVerticesNextIter);
	}

	std::vector<std::thread> threadPool;

	//Use the search space reduced adjacency list
	if (searchSpaceReduce) {
		//Start all of the threads
		for (int threadIndex = 0; threadIndex < pathsToSearch.size(); threadIndex++) {
			threadPool.push_back(std::thread(DijkstrasAlgorithm::singleSourceShortestPath, pathsToSearch.at(threadIndex).startVertex, 
			pathsToSearch.at(threadIndex).endVertex, reducedAdjList1, std::ref(pathsToSearch.at(threadIndex).pathInformation), 0, 0, true));
		}
	}
	//Use the non-search space reduced adjacency list
	else {
		for (int threadIndex = 0; threadIndex < pathsToSearch.size(); threadIndex++) {
			threadPool.push_back(std::thread(DijkstrasAlgorithm::singleSourceShortestPath, pathsToSearch.at(threadIndex).startVertex, 
			pathsToSearch.at(threadIndex).endVertex, adjacencyList, std::ref(pathsToSearch.at(threadIndex).pathInformation), 0, 0, true));
		}
	}

	//Join the threads
	for (int threadIndex = 0; threadIndex < pathsToSearch.size(); threadIndex++) {
		threadPool.at(threadIndex).join();
	}

	//Remove any paths that weren't valid
	pathsToSearch.erase(remove_if(pathsToSearch.begin(), pathsToSearch.end(), erase_func()), pathsToSearch.end());

	//Sort in ascending order
	sort(pathsToSearch.begin(), pathsToSearch.end(), sort_func());

	//Display path information
	if (debug) {
		for (int temp = 0; temp < pathsToSearch.size(); temp++) {
			output << pathsToSearch.at(temp).pathInformation.toString() << std::endl;
		}
		output << std::endl;
	}
	
	//Kruskal's algorithm
	pathCount = 0;
	for (int pathIndex = 0; pathIndex < pathsToSearch.size(); pathIndex++) {
		//If either of the vertices hasn't been added to the set, add one or both;
		//Add the path to the list of shortest paths
		if (verticesFound.count(pathsToSearch.at(pathIndex).pathInformation.getPathAt(0)) == 0 || 
			verticesFound.count(pathsToSearch.at(pathIndex).pathInformation.getPathAt(pathsToSearch.at(pathIndex).pathInformation.getPathLength())) == 0) {
				
			shortestPaths.push_back(PathInformation());
			shortestPaths.at(pathCount).setPath(pathsToSearch.at(pathIndex).pathInformation.getPath());
			shortestPaths.at(pathCount).setPathLength(pathsToSearch.at(pathIndex).pathInformation.getPathLength());

			verticesFound.insert(pathsToSearch.at(pathIndex).pathInformation.getPathAt(0));
			verticesFound.insert(pathsToSearch.at(pathIndex).pathInformation.getPathAt(pathsToSearch.at(pathIndex).pathInformation.getPathLength()));
			pathCount++;
		}
	}

	//Check to make sure that every vertex has been accounted for in a path,
	//if it hasn't and it exists in the adj list, add it

	//Loop through each vertex in the vertices to search for
	for (int vertexIndex = 0; vertexIndex < verticesToSearch.size(); vertexIndex++) {
		//Check to see if the vertex has been found, if it hasn't procede 
		if(verticesFound.count(verticesToSearch.at(vertexIndex)) == 0) {
			//Check to see if the vertex exists in the adj list
			if (adjacencyList.getVertexConnectionCount(verticesToSearch.at(vertexIndex)) > 0) {
				std::vector<int> tempList;
				tempList.push_back(verticesToSearch.at(vertexIndex));

				shortestPaths.push_back(PathInformation());
				shortestPaths.at(pathCount).setPath(tempList);
				shortestPaths.at(pathCount).setPathLength(tempList.size() - 1);

				pathCount++;
			}
		}
	}

	return shortestPaths;
}