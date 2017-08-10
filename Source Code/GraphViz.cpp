/*
 * GraphViz.cpp
 *
 *  Created on: N/A
 *      Author: Scott Freitas
 */

#include "GraphViz.h"


void GraphViz::convertKSSPAdjListToDOT(const AdjacencyList &nonSearchReducedAdjList, const AdjacencyList &adjList, 
										const std::vector<std::vector<int>> &keyVertices, const std::vector<PathInformation> 
										&shortestPaths, const std::unordered_map<int, std::string> &nameList, bool useNameList, 
										int colorSchemeFilter, std::string nodeSize, int edgeSchemeFilter, std::string dotFileLocation, 
										std::string dotFileLocationDefaultFont, std::string adjListLocation) {

	AdjacencyList adjListCopy = adjList;
	std::string graphInput = "graph b { \n";
	std::vector<int> firstEdgeSet;
	std::vector<int> secondEdgeSet;
	std::set<int> numberOfUniqueVertices;
	int colorIndex = 0;

	const std::string colors[] = { "#FF0013", "#FF4F00", /*"#FF8900",*/ "#FFB300", /*"#FFD600",*/ "#FFEF00", /*"#E4FF00",*/ "#81FF00",
									"#00FF5F", "#00FFFF", "#05ADFF", "#0A6DFF", "#0E2FFF", "#670AFF", "#9707FF", "#C204FF", "#EE01FF", 
									"#FF00E9", "#FF00B9", "#FF0074" };
	//const string colors[] = { "lightcyan", "paleturquoise", "lightblue1", "lightskyblue", "skyblue", "turquoise3", "steelblue4", "dodgerblue4", 
								//"plum1", "pink1", "pink2", "pink3", "violet", "lightgoldenrod1", "goldenrod1", "goldenrod3", "lightpink2", 
								//"tomato", "tomato3", "brown1" };


	const std::vector<std::string> standardColors = { "blue", "green", "lightgoldenrod1", "indianred1" };
	//light green, light blue, light purple, dark blue
	const std::vector<std::string> neonColors1 = { "#3DFF00", "#00FFFF", "#e066ff", "#1097FF" };
	//light blue, light purple, fluorescentish green, darker blue
	const std::vector<std::string> neonColors2 = { "#00FFFF", "#e066ff", "#00FF6F", "#1097FF" };
	//light purple, darker blue, light blue, light green
	const std::vector<std::string> neonColors3 = { "#e066ff", "#1097FF", "#00FFFF", "#3DFF00" };
	//fluorescentish green, darker blue, light purple, bright blue
	const std::vector<std::string> neonColors4 = { "#00FF6F", "#1097FF", "#e066ff", "#00FFFF" };
	//light purple, bright blue, darker blue, fluorescentish green
	const std::vector<std::string> neonColors5 = { "#e066ff", "#00FFFF", "#1097FF", "#00FF6F" };

	const std::vector<std::string> neonColors6 = { "#e066ff", "#00FFFF", "#3DFF00", "#F8FF00" };

	std::vector<std::vector<std::string>> colorSchemes = { neonColors1, neonColors2, neonColors3, neonColors4, neonColors5, neonColors6, 
															standardColors};
	std::vector<std::string> colorScheme = colorSchemes.at(colorSchemeFilter);

	//Graph the vertices
	graphVertices(nonSearchReducedAdjList, adjListCopy, keyVertices, graphInput, nameList, useNameList, colorScheme, nodeSize);

	//Label each shortest path with a different edge color
	for (int pathIndex = 0; pathIndex < shortestPaths.size(); pathIndex++) {
		for (int vertexIndex = 0; vertexIndex < shortestPaths.at(pathIndex).getPathLength(); vertexIndex++) {

			std::string label = "";
			std::string otherLabel = "";

			//If true, set the label as the name
			if (useNameList) {
				label = "\"" + nameList.at(shortestPaths.at(pathIndex).getPathAt(vertexIndex)) + "\"";
				otherLabel = "\"" + nameList.at(shortestPaths.at(pathIndex).getPathAt(vertexIndex + 1)) + "\"";
			}
			//Otherwise use the vertex number
			else {
				label = std::to_string(shortestPaths.at(pathIndex).getPathAt(vertexIndex));
				otherLabel = std::to_string(shortestPaths.at(pathIndex).getPathAt(vertexIndex + 1));
			}

			graphInput = graphInput + label + " -- " + otherLabel + "[color = \"" + colors[colorIndex] + "\", penwidth = 5];\n";
		
			//Keep track of edges and vertices
			firstEdgeSet.push_back(shortestPaths.at(pathIndex).getPathAt(vertexIndex));
			secondEdgeSet.push_back(shortestPaths.at(pathIndex).getPathAt(vertexIndex + 1));
			numberOfUniqueVertices.insert(shortestPaths.at(pathIndex).getPathAt(vertexIndex));
			numberOfUniqueVertices.insert(shortestPaths.at(pathIndex).getPathAt(vertexIndex + 1));	
		}
		colorIndex++;
		if (colorIndex == 20) {
			colorIndex = 0;
		}
	}

	//Graph the edges
	//If the color scheme is 1 use gray edges
	if (edgeSchemeFilter == 0) {
		graphEdges(adjListCopy, keyVertices, shortestPaths, graphInput, firstEdgeSet, secondEdgeSet, numberOfUniqueVertices, 
					useNameList, nameList);
	}
	//Otherwise use colored edges
	else {
		graphEdgesColored(adjListCopy, keyVertices, shortestPaths, graphInput, colorScheme, firstEdgeSet, secondEdgeSet, 
							numberOfUniqueVertices, useNameList, nameList);
	}

	//Save the DOT graph information to a file
	saveDOTFile(graphInput, nodeSize, dotFileLocation, dotFileLocationDefaultFont);
	//Save the graph visualization information in adjacency list format
	saveAdjListFile(adjListLocation, firstEdgeSet, secondEdgeSet, numberOfUniqueVertices, nameList, useNameList);
}


void GraphViz::convertMSTAdjListToDOT(const AdjacencyList &nonSearchReducedAdjList, const AdjacencyList &adjList, 
										const std::vector<std::vector<int>> &keyVertices, const std::vector<PathInformation> 
										&shortestPaths, const  std::unordered_map<int, std::string> &nameList, bool useNameList, 
										int colorSchemeFilter, std::string nodeSize, int edgeSchemeFilter, std::string dotFileLocation, 
										std::string dotFileLocationDefaultFont, std::string adjListLocation) {
	
	AdjacencyList adjListCopy = adjList;
	std::set< std::pair<int, int> > edgesAdded;

	const std::vector<std::string> standardColors = { "blue", "green", "lightgoldenrod1", "indianred1" };
	//light green, light blue, light purple, dark blue
	const std::vector<std::string> neonColors1 = { "#3DFF00", "#00FFFF", "#e066ff", "#1097FF" };
	//light blue, light purple, fluorescentish green, darker blue
	const std::vector<std::string> neonColors2 = { "#00FFFF", "#e066ff", "#00FF6F", "#1097FF" };
	//light purple, darker blue, light blue, light green
	const std::vector<std::string> neonColors3 = { "#e066ff", "#1097FF", "#00FFFF", "#3DFF00" };
	//fluorescentish green, darker blue, light purple, bright blue
	const std::vector<std::string> neonColors4 = { "#00FF6F", "#1097FF", "#e066ff", "#00FFFF" };
	//light purple, bright blue, darker blue, fluorescentish green
	const std::vector<std::string> neonColors5 = { "#e066ff", "#00FFFF", "#1097FF", "#00FF6F" };

	const std::vector<std::string> neonColors6 = { "#e066ff", "#00FFFF", "#3DFF00", "#F8FF00" };

	std::vector<std::vector<std::string>> colorSchemes = { neonColors1, neonColors2, neonColors3, neonColors4, neonColors5, neonColors6, 
															standardColors };
	std::vector<std::string> colorScheme = colorSchemes.at(colorSchemeFilter);

	std::string graphInput = "graph b { \n";
	std::vector <int> firstEdgeSet;
	std::vector <int> secondEdgeSet;
	std::set<int> numberOfUniqueVertices;

	//Graph the vertices
	graphVertices(nonSearchReducedAdjList, adjListCopy, keyVertices, graphInput, nameList, useNameList, colorScheme, nodeSize);

	//Add each edge in the MST
	//Loop through each path
	for (int pathIndex = 0; pathIndex < shortestPaths.size(); pathIndex++) {
		//Loop through each vertex in the path
		for (int vertexIndex = 0; vertexIndex < shortestPaths.at(pathIndex).getPathLength(); vertexIndex++) {
			std::pair <int, int> tempPair(shortestPaths.at(pathIndex).getPathAt(vertexIndex), 
											shortestPaths.at(pathIndex).getPathAt(vertexIndex + 1));
			std::pair <int, int> tempPair2(shortestPaths.at(pathIndex).getPathAt(vertexIndex + 1), 
											shortestPaths.at(pathIndex).getPathAt(vertexIndex));
			
			std::string label = "";
			std::string otherLabel = "";

			//If true, set the label as the name
			if (useNameList) {
				label = "\"" + nameList.at(shortestPaths.at(pathIndex).getPathAt(vertexIndex)) + "\"";
				otherLabel = "\"" + nameList.at(shortestPaths.at(pathIndex).getPathAt(vertexIndex + 1)) + "\"";
			}
			//Otherwise use the vertex number
			else {
				label = std::to_string(shortestPaths.at(pathIndex).getPathAt(vertexIndex));
				otherLabel = std::to_string(shortestPaths.at(pathIndex).getPathAt(vertexIndex + 1));
			}

			//If this pair hasn't already been added, add it and graph it
			if (edgesAdded.count(tempPair) == 0 && edgesAdded.count(tempPair2) == 0) {
				graphInput = graphInput + label + " -- " + otherLabel + "[color = \"red\", penwidth = 5];\n";
				edgesAdded.insert(tempPair);
				edgesAdded.insert(tempPair2);

				//Keep track of edges and vertices
				firstEdgeSet.push_back(shortestPaths.at(pathIndex).getPathAt(vertexIndex));
				secondEdgeSet.push_back(shortestPaths.at(pathIndex).getPathAt(vertexIndex + 1));
				numberOfUniqueVertices.insert(shortestPaths.at(pathIndex).getPathAt(vertexIndex));
				numberOfUniqueVertices.insert(shortestPaths.at(pathIndex).getPathAt(vertexIndex + 1));
			}
		}
	}

	//Graph the edges
	//If the edge color scheme is 0 use gray edges
	if (edgeSchemeFilter == 0) {
		graphEdges(adjListCopy, keyVertices, shortestPaths, graphInput, firstEdgeSet, secondEdgeSet, numberOfUniqueVertices, 
					useNameList, nameList);
	}
	//Otherwise use colored edges
	else {
		graphEdgesColored(adjListCopy, keyVertices, shortestPaths, graphInput, colorScheme, firstEdgeSet, secondEdgeSet, 
							numberOfUniqueVertices, useNameList, 
		nameList);
	}

	//Save the DOT graph information to a file
	saveDOTFile(graphInput, nodeSize, dotFileLocation, dotFileLocationDefaultFont);
	//Save the graph visualization information in adjacency list format
	saveAdjListFile(adjListLocation, firstEdgeSet, secondEdgeSet, numberOfUniqueVertices, nameList, useNameList);
}

void GraphViz::graphVertices(const AdjacencyList &nonSearchReducedAdjList, AdjacencyList &adjListCopy, const std::vector<std::vector<int>> 
								&keyVertices, std::string &graphInput, const std::unordered_map<int, std::string> &nameList, bool useNameList,
	std::vector<std::string> colorScheme, std::string nodeSize) {
	time_t date = time(0);
	char* dt = ctime(&date);

	graphInput = graphInput + "graph [label = \"Network Analysis \n Date Created: " + dt + "\", labelloc = t, fontsize = 40, "
								"overlap=prism, outputorder=edgesfirst];";

	//Go through each vertex and label it
	for (int index = 0; index < adjListCopy.size(); index++) {
		std::string label = "";
		std::string label2 = "";
		std::string fontSize = "fontsize = " + nodeSize;
		std::string critFontSize = "fontsize = " + nodeSize;
		if (stoi(nodeSize) <= 6) {
			critFontSize = "fontsize = " + std::to_string(stoi(nodeSize) + 2);
		}


		//If true, set the label as the name
		if (useNameList) {
			label = "\"" + nameList.at(index) + "\"";
			label2 = nameList.at(index);
		}
		//Otherwise use the vertex number
		else {
			label = std::to_string(index);
			label2 = std::to_string(index);
		}

		//Make sure that the current vertex is not a user defined node or path vertex
		if (std::find(keyVertices[0].begin(), keyVertices[0].end(), index) == keyVertices[0].end() 
			&& std::find(keyVertices[1].begin(), keyVertices[1].end(), index) == keyVertices[1].end()) {

			//Four hops away
			if (adjListCopy.getInfoValue(index) > 3) {
				graphInput = graphInput + label + "[label = \"" + label2 + "\n CC: " 
								+ std::to_string(nonSearchReducedAdjList.getVertexConnectionCount(index)) + "\" , " + fontSize 
								+ ", style = filled, color = \"" + colorScheme[3] + "\", fixedsize = true, height = 1, width = 1];";
			}

			//Three hops away
			else if (adjListCopy.getInfoValue(index) == 3) {
				graphInput = graphInput + label + "[label = \"" + label2 + "\n CC: " 
								+ std::to_string(nonSearchReducedAdjList.getVertexConnectionCount(index)) + "\" , " + fontSize 
								+ ", style = filled, color = \"" + colorScheme[2] + "\", fixedsize = true, height = 1, width = 1];";
			}

			//Two hops away
			else if (adjListCopy.getInfoValue(index) == 2) {
				graphInput = graphInput + label + "[label = \"" + label2 + "\n CC: " 
								+ std::to_string(nonSearchReducedAdjList.getVertexConnectionCount(index)) + "\" , " + fontSize 
								+ ", style = filled, color = \"" + colorScheme[1] + "\", fixedsize = true, height = 1, width = 1];";
			}

			//One hop away
			else if (adjListCopy.getInfoValue(index) == 1) {
				graphInput = graphInput + label + "[label = \"" + label2 + "\n CC: " 
								+ std::to_string(nonSearchReducedAdjList.getVertexConnectionCount(index)) + "\" , " + fontSize 
								+ ", style = filled, color = \"" + colorScheme[0] + "\", fixedsize = true, height = 1, width = 1];";
			}
		}


		//Check to see if the current vertex is a user defined vertex
		for (int keyIndex = 0; keyIndex < keyVertices[0].size(); keyIndex++) {
			if (index == keyVertices[0].at(keyIndex)) {
				graphInput = graphInput + label + "[label = \"" + label2 + "\n CC: " 
								+ std::to_string(nonSearchReducedAdjList.getVertexConnectionCount(index)) + "\" , " + critFontSize 
								+ ", shape = hexagon, style = filled, color = red, fixedsize = true, height = 1, width = 1];";
			}
		}

		//Check to see if the current vertex is a path vertex
		for (int keyIndex = 0; keyIndex < keyVertices[1].size(); keyIndex++) {
			if (index == keyVertices[1].at(keyIndex)) {
				graphInput = graphInput + label + "[label = \"" + label2 + "\n CC: " 
								+ std::to_string(nonSearchReducedAdjList.getVertexConnectionCount(index)) + "\" , " + critFontSize 
								+ ", shape = hexagon, style = filled, color = orange, fixedsize = true, height = 1, width = 1];";
			}
		}
	}
}

void GraphViz::graphEdges(AdjacencyList &adjListCopy, const std::vector<std::vector<int>> &keyVertices, 
							const std::vector<PathInformation> &shortestPaths, std::string &graphInput, 
							std::vector<int> &firstEdgeSet, std::vector<int> &secondEdgeSet, std::set<int> 
							&numberOfUniqueVertices, bool useNameList, const std::unordered_map<int, std::string> &nameList) {

	//Go through each edge and label it as long as it's not a vertex on the MST or path
	for (int index = 0; index < adjListCopy.size(); index++) {
		std::string label = "";
		bool procede = true;
		//Check to see if the current vertex is a path or start/end vertex
		for (int pathIndex = 0; pathIndex < shortestPaths.size(); pathIndex++) {
			for (int vertexIndex = 0; vertexIndex <= shortestPaths.at(pathIndex).getPathLength(); vertexIndex++) {
				if (index == shortestPaths.at(pathIndex).getPathAt(vertexIndex)) {
					procede = false;
				}
			}
		}

		if (procede) {
			std::vector<int> edgesToDelete;

			//If true, set the label as the name
			if (useNameList) {
				label = "\"" + nameList.at(index) + "\"";
			}
			//Otherwise use the vertex number
			else {
				label = std::to_string(index);
			}

			//Go through each of the vertex's edges and add it to the graph
			for (int edgeCount = 0; edgeCount < adjListCopy.getVertexConnectionCount(index); edgeCount++) {

				std::string otherLabel = "";
				//If true, set the otherLabel as the name
				if (useNameList) {
					otherLabel = "\"" + nameList.at(adjListCopy.getVertexData(index, edgeCount)) + "\"";
				}
				//Otherwise use the vertex number
				else {
					otherLabel = std::to_string(adjListCopy.getVertexData(index, edgeCount));
				}

				graphInput = graphInput + label + " -- " + otherLabel + "[color = \"#606060\", penwidth = 0.25];\n";
				edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));

				//Keep track of edges and vertices
				firstEdgeSet.push_back(index);
				secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
				numberOfUniqueVertices.insert(index);
				numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
			}

			//Delete the edges that were graphed
			for (int edgeIndex = 0; edgeIndex < edgesToDelete.size(); edgeIndex++) {
				adjListCopy.removeEdge(index, edgesToDelete.at(edgeIndex));
			}
		}
	}
}

void GraphViz::graphEdgesColored(AdjacencyList &adjListCopy, const std::vector<std::vector<int>> &keyVertices, 
									const std::vector<PathInformation> &shortestPaths, std::string &graphInput, 
									std::vector<std::string> colorScheme, std::vector<int> &firstEdgeSet, 
									std::vector<int> &secondEdgeSet, std::set<int> &numberOfUniqueVertices, 
									bool useNameList, const std::unordered_map<int, std::string> &nameList) {

	//Go through each edge and label it as long as it's not a vertex on the MST or path
	for (int index = 0; index < adjListCopy.size(); index++) {
		std::string label = "";
		bool procede = true;
		//Check to see if the current vertex is a path vertex
		for (int pathIndex = 0; pathIndex < shortestPaths.size(); pathIndex++) {
			for (int vertexIndex = 0; vertexIndex <= shortestPaths.at(pathIndex).getPathLength(); vertexIndex++) {
				if (index == shortestPaths.at(pathIndex).getPathAt(vertexIndex)) {
					procede = false;
				}
			}
		}

		if (procede) {
			std::vector<int> edgesToDelete;

			//If true, set the label as the name
			if (useNameList) {
				label = "\"" + nameList.at(index) + "\"";
			}
			//Otherwise use the vertex number
			else {
				label = std::to_string(index);
			}

			if (adjListCopy.getInfoValue(index) == 1) {
				//Go through each of the vertex's edges
				for (int edgeCount = 0; edgeCount < adjListCopy.getVertexConnectionCount(index); edgeCount++) {
					int otherVertex = adjListCopy.getVertexData(index, edgeCount);

					std::string otherLabel = "";
					//If true, set the otherLabel as the name
					if (useNameList) {
						otherLabel = "\"" + nameList.at(adjListCopy.getVertexData(index, edgeCount)) + "\"";
					}
					//Otherwise use the vertex number
					else {
						otherLabel = std::to_string(adjListCopy.getVertexData(index, edgeCount));
					}

					//Check to see if the other vertex is a user vertex or a path vertex
					if (find(keyVertices[0].begin(), keyVertices[0].end(), otherVertex) != keyVertices[0].end() 
						|| find(keyVertices[1].begin(), keyVertices[1].end(), otherVertex) != keyVertices[1].end())  {

						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"" + colorScheme[0] + "\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}
					else if (adjListCopy.getInfoValue(otherVertex) == 1) {
						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"#606060\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}
					else if (adjListCopy.getInfoValue(otherVertex) == 2) {
						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"" + colorScheme[1] + "\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}
					else if (adjListCopy.getInfoValue(otherVertex) == 3) {
						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"#606060\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}
					else if (adjListCopy.getInfoValue(otherVertex) > 3) {
						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"#606060\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}

				}
			}

			else if (adjListCopy.getInfoValue(index) == 2) {
				//Go through each of the vertex's edges
				for (int edgeCount = 0; edgeCount < adjListCopy.getVertexConnectionCount(index); edgeCount++) {
					int otherVertex = adjListCopy.getVertexData(index, edgeCount);

					std::string otherLabel = "";
					//If true, set the otherLabel as the name
					if (useNameList) {
						otherLabel = "\"" + nameList.at(adjListCopy.getVertexData(index, edgeCount)) + "\"";
					}
					//Otherwise use the vertex number
					else {
						otherLabel = std::to_string(adjListCopy.getVertexData(index, edgeCount));
					}

					//Check to see if the other vertex is a user vertex or a path vertex
					if (find(keyVertices[0].begin(), keyVertices[0].end(), otherVertex) != keyVertices[0].end() 
						|| find(keyVertices[1].begin(), keyVertices[1].end(), otherVertex) != keyVertices[1].end())  {

						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"" + colorScheme[1] + "\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}
					else if (adjListCopy.getInfoValue(otherVertex) == 1) {
						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"" + colorScheme[1] + "\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}
					else if (adjListCopy.getInfoValue(otherVertex) == 2) {
						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"#606060\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}
					else if (adjListCopy.getInfoValue(otherVertex) == 3) {
						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"" + colorScheme[2] + "\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}
					else if (adjListCopy.getInfoValue(otherVertex) > 3) {
						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"#606060\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}

				}
			}

			else if (adjListCopy.getInfoValue(index) == 3) {
				//Go through each of the vertex's edges
				for (int edgeCount = 0; edgeCount < adjListCopy.getVertexConnectionCount(index); edgeCount++) {
					int otherVertex = adjListCopy.getVertexData(index, edgeCount);

					std::string otherLabel = "";
					//If true, set the otherLabel as the name
					if (useNameList) {
						otherLabel = "\"" + nameList.at(adjListCopy.getVertexData(index, edgeCount)) + "\"";
					}
					//Otherwise use the vertex number
					else {
						otherLabel = std::to_string(adjListCopy.getVertexData(index, edgeCount));
					}

					//Check to see if the other vertex is a user vertex or a path vertex
					if (find(keyVertices[0].begin(), keyVertices[0].end(), otherVertex) != keyVertices[0].end() 
						|| find(keyVertices[1].begin(), keyVertices[1].end(), otherVertex) != keyVertices[1].end()) {

						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"" + colorScheme[2] + "\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}
					else if (adjListCopy.getInfoValue(otherVertex) == 1) {
						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"#606060\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}
					else if (adjListCopy.getInfoValue(otherVertex) == 2) {
						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"" + colorScheme[2] + "\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}
					else if (adjListCopy.getInfoValue(otherVertex) == 3) {
						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"#606060\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}
					else if (adjListCopy.getInfoValue(otherVertex) > 3) {
						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"" + colorScheme[3] + "\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}

				}
			}

			else if (adjListCopy.getInfoValue(index) > 3) {
				//Go through each of the vertex's edges
				for (int edgeCount = 0; edgeCount < adjListCopy.getVertexConnectionCount(index); edgeCount++) {
					int otherVertex = adjListCopy.getVertexData(index, edgeCount);

					std::string otherLabel = "";
					//If true, set the otherLabel as the name
					if (useNameList) {
						otherLabel = "\"" + nameList.at(adjListCopy.getVertexData(index, edgeCount)) + "\"";
					}
					//Otherwise use the vertex number
					else {
						otherLabel = std::to_string(adjListCopy.getVertexData(index, edgeCount));
					}

					//Check to see if the other vertex is a user vertex or a path vertex
					if (find(keyVertices[0].begin(), keyVertices[0].end(), otherVertex) != keyVertices[0].end() 
						|| find(keyVertices[1].begin(), keyVertices[1].end(), otherVertex) != keyVertices[1].end())  {
							
						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"" + colorScheme[3] + "\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}
					else if (adjListCopy.getInfoValue(otherVertex) == 1) {
						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"#606060\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}
					else if (adjListCopy.getInfoValue(otherVertex) == 2) {
						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"#606060\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}
					else if (adjListCopy.getInfoValue(otherVertex) == 3) {
						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"" + colorScheme[3] + "\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}
					else if (adjListCopy.getInfoValue(otherVertex) > 3) {
						graphInput = graphInput + label + " -- " + otherLabel + "[color = \"#606060\", penwidth = 0.25];\n";
						edgesToDelete.push_back(adjListCopy.getVertexData(index, edgeCount));
						//Keep track of edges and vertices
						firstEdgeSet.push_back(index);
						secondEdgeSet.push_back(adjListCopy.getVertexData(index, edgeCount));
						numberOfUniqueVertices.insert(index);
						numberOfUniqueVertices.insert(adjListCopy.getVertexData(index, edgeCount));
					}

				}
			}

			//Delete the edges that were graphed
			for (int edgeIndex = 0; edgeIndex < edgesToDelete.size(); edgeIndex++) {
				adjListCopy.removeEdge(index, edgesToDelete.at(edgeIndex));
			}
		}
	}
}

void GraphViz::saveAdjListFile(std::string adjListLocation, std::vector<int> &firstEdgeSet, std::vector<int> &secondEdgeSet, 
								std::set<int> &numberOfUniqueVertices, const std::unordered_map<int, std::string> &nameList, 
								bool useNameList) {

	std::ofstream out(adjListLocation);
	//Output the number of unique vertices
	out << std::to_string(numberOfUniqueVertices.size()) + "\n";
	//Output the number of edges
	out << std::to_string(firstEdgeSet.size()) + "\n";
	//Output each pair of edges
	for (int index = 0; index < firstEdgeSet.size(); index++) {
		//Print the string reprsentation if a name list is used
		if (useNameList) {
			out << nameList.at(firstEdgeSet.at(index)) + " " + nameList.at(secondEdgeSet.at(index))  + "\n";
		}
		//Otherwise print the integer representation
		else {
			out << std::to_string(firstEdgeSet.at(index)) + " " + std::to_string(secondEdgeSet.at(index))  + "\n";
		}
	}
	out.close();
}

void GraphViz::saveDOTFile(std::string graphInput, std::string nodeSize, std::string dotFileLocation, 
							std::string dotFileLocationDefaultFont) {

	//Print closing graph info
	graphInput = graphInput + "\n}";

	std::ofstream out(dotFileLocation);
	out << graphInput;
	out.close();

	//Print closing graph info
	std::string graphInput2 = graphInput;

	std::string fontSize = "fontsize = " + nodeSize;
	std::string critFontSize = "fontsize = " + nodeSize;
	if (stoi(nodeSize) <= 6) {
		critFontSize = "fontsize = " + std::to_string(stoi(nodeSize) + 2);
	}

	std::string defaultFontSize = "fontsize = 12";
	size_t index = 0;
	int numberOfIterations = 0;
	while (true) {
		//Find the substring to replace
		index = graphInput2.find(fontSize, index);
		if (index == std::string::npos) break;

		//Ignore the header text
		if (numberOfIterations > 0) {
			//Replace the substring with the new substring
			graphInput2.replace(index, 13, defaultFontSize);
		}

		//Move the index forward
		index += 13;
	}

	index = 0;
	while (true) {
		//Find the substring to replace
		index = graphInput2.find(critFontSize, index);
		if (index == std::string::npos) break;

		//Ignore the header text
		if (numberOfIterations > 0) {
			//Replace the substring with the new substring
			graphInput2.replace(index, 13, defaultFontSize);
		}

		//Move the index forward
		index += 13;
	}

	std::ofstream out2(dotFileLocationDefaultFont);
	out2 << graphInput2;
	out2.close();
}