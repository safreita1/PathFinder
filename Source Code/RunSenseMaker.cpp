#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <ctime>
#include <vector>
#include <stdio.h>
#include <unordered_map>
#include <chrono>
#include <cstring>

#include "KSimpleShortestPaths.h"
#include "MST.h"
#include "Parsing.h"

int main(int argc, char *argv[]) {
	AdjacencyList adjacencyList = AdjacencyList();
	std::unordered_map<int, std::string> nameList;
	std::unordered_map<std::string, int> nameListKey;
	std::vector<std::string> programInfo;

	std::ofstream output;
	bool useNameList = false;
	bool debug = true;
	bool useKSSP = true;
	int exitCode = 1;
	std::chrono::steady_clock::time_point startTime, endTime;
	std::chrono::steady_clock::time_point totalTimeStart, totalTimeEnd;

	//Put command line parameters into vector<string>
	//Max vertex is 43, vertex 41 will never be used
	for (int index = 1; index < argc; index++) {
		programInfo.push_back(argv[index]);
	}

	//General program parameters
	std::istringstream(programInfo.at(21)) >> std::boolalpha >> useNameList;
	std::string pathToNetworkFile = programInfo.at(0);
	std::string instruction = programInfo.at(1);
	std::istringstream(programInfo.at(43)) >> std::boolalpha >> useKSSP;


	//Open the time measurement file for writing
	if (debug) {
		std::string fileLocation = "/path_finder_files/TimeMeasurements.txt";
		output.open(fileLocation);
	}

	//Get all the input variables to the program
	if (debug) {
		std::string fileLocation = "/path_finder_files/inputvariables.txt";
		std::ofstream output2(fileLocation);
		output2 << "Size: " << programInfo.size() << std::endl;
		for (int index = 0; index < argc - 1; index++) {
		output2 << programInfo.at(index) << std::endl;
		}
		output2.close();
	}

	//Start recording the total time elapsed
	if (debug) {
		totalTimeStart = std::chrono::steady_clock::now();
	}

	//Start recording the time elapsed
	if (debug) {
		startTime = std::chrono::steady_clock::now();
	}

	//Determine which type of text file is being read in
	if (useNameList) {
		Parsing::getNamedGraphData(pathToNetworkFile, adjacencyList, nameList, nameListKey);
	}
	else {
		//Gets the graph data stores it in the data structure
		Parsing::getGraphData(pathToNetworkFile, adjacencyList);
	}

	//End time
	if (debug) {
		endTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsedTime = endTime - startTime;
		output << "Time to parse the file: " << elapsedTime.count() << " seconds." << std::endl;
		output << std::endl;
	}

	//Remove user specified vertices and edges from the adjacency list
	Parsing::removeVertices(adjacencyList, nameListKey, programInfo, useNameList);
	Parsing::removeEdges(adjacencyList, nameListKey, programInfo, useNameList);

	//KSSP algorithm
	if (instruction == "KSSP") {
		exitCode = KSimpleShortestPaths::runKSSP(adjacencyList, programInfo, output, debug, nameListKey, nameList, useKSSP);
	}

	//Shortest Paths MST algorithm
	else if (instruction == "MST") {
		exitCode = MST::runMST(adjacencyList, programInfo, output, debug, nameListKey, nameList);
	}

	//End time
	if (debug) {
		totalTimeEnd = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsedTime = totalTimeEnd - totalTimeStart;
		output << "Time to run the program: " << elapsedTime.count() << " seconds." << std::endl;
		output << std::endl;
	}
	
	output.close();
	return exitCode;
}
