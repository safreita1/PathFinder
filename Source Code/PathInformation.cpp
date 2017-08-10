/*
 * PathInformation.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: scott
 */

#include "PathInformation.h"

/**
 * Constructor.
 * Creates an empty string for path and sets pathLength to 0.
 */
PathInformation::PathInformation() {
	pathLength = 0;
}

/**
 * Constructor.
 * @parameter tempPath  Initializes path with tempPath.
 * @parameter tempPathLength  Initializes the pathLength with tempPathLength.
 */
PathInformation::PathInformation(std::vector<int> updatedPath, int updatedPathLength) {
	path = updatedPath;
	pathLength = updatedPathLength;
}

/**
 * Gets the path.
 * @return a string with the path information
 */
int PathInformation::getPathAt(int index) const {
	return path.at(index);
}

std::vector<int> PathInformation::getPath() const {
	return path;
}

/**
 * Sets the path
 * @parameter updatedPath  Sets the path to updatedPath.
 */
void PathInformation::setPath(std::vector<int> updatedPath) {
	this->path = updatedPath;
}

/**
 * Returns the path length
 * @return the pathLength
 */
int PathInformation::getPathLength() const {
	return pathLength;
}

/**
 * Sets the path length
 * @parameter tempPathLength  Sets the pathLength to updatedPathLength.
 */
void PathInformation::setPathLength(int updatedPathLength) {
	pathLength = updatedPathLength;
}


/**
 * Returns the path and pathLength
 * @return a string that contains the path and pathLength
 */
std::string PathInformation::toString() const {
	std::stringstream pathLen;
	std::stringstream pathData;
	std::string info;

	pathLen << pathLength;
	copy(this->path.begin(), this->path.end(), std::ostream_iterator<int>(pathData, " "));
	
	info = pathData.str() + ". Length: " + pathLen.str();

	return info;
}

/**
 * Compares two PathInformation objects.
 * @return true if the paths are equal, false otherwise
 */
bool PathInformation::equals(PathInformation other) const {
	return (path == other.path);
}


